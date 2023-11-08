#include "AssortmentMapper.h"
#include <iostream>

AssortmentMapper::AssortmentMapper(DBConnection* conn) {
    this->conn = conn;
}

AssortmentMapper::~AssortmentMapper() {
}

void putPQResToList(PGresult* res, std::vector<Assortment>& assortmentList) {
    int ncols = PQnfields(res);
    for (int i = 0; i < ncols; i++) {
        char* name = PQfname(res, i);
        printf("%s ", name);
    }
    printf("\n");

    int nrows = PQntuples(res);
    for (int i = 0; i < nrows; i++) {
        char* id = PQgetvalue(res, i, 0);
        char* supplierId = PQgetvalue(res, i, 1);
        char* wholesalePrice = PQgetvalue(res, i, 2);
        char* deliveryTerms = PQgetvalue(res, i, 3);
        char* paymentTerms = PQgetvalue(res, i, 4);
        assortmentList.push_back(Assortment(atoi(id), atoi(supplierId), atof(wholesalePrice), deliveryTerms, paymentTerms));
    }
}

std::vector<Assortment> AssortmentMapper::getBySupplierName(std::string name) {
    PGresult* res;
    char query[200];
    std::vector<Assortment> assortmentList;
    snprintf(query, sizeof(query), "SELECT a.id, a.supplier_id, a.wholesale_price, a.delivery_terms, a.payment_terms FROM assortments a JOIN suppliers s ON a.supplier_id = s.id WHERE s.name = '%s';", name.c_str());
    res = PQexec(conn->conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("res != PGRES_TUPLES_OK\n");
        printf("Error message: %s\n", PQerrorMessage(conn->conn));
    }
    putPQResToList(res, assortmentList);
    if (res != NULL) {
        PQclear(res);
        res = NULL;
    }
    return assortmentList;
}

std::vector<Assortment> AssortmentMapper::getAll() {
    PGresult* res;
    char query[100];
    std::vector<Assortment> assortmentList;
    snprintf(query, sizeof(query), "SELECT id, supplier_id, wholesale_price, delivery_terms, payment_terms FROM assortments;");
    res = PQexec(conn->conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("res != PGRES_TUPLES_OK\n");
        printf("Error message: %s\n", PQerrorMessage(conn->conn));
    }

    putPQResToList(res, assortmentList);
    if (res != NULL) {
        PQclear(res);
        res = NULL;
    }
    return assortmentList;
}

bool AssortmentMapper::save(Assortment& assortment) {
    bool ret = true;
    PGresult* res = NULL;
    if (assortment.getId() != 0) {
        char query[] =
            "UPDATE assortments SET supplier_id = $2, wholesale_price = $3, delivery_terms = $4, payment_terms = $5"
            " WHERE id = $1;";
        const char* params[5];
        std::string* assortmentString = assortment.getString();
        for (size_t i = 0; i < 5; i++)
            params[i] = assortmentString[i].c_str();
        res = PQexecParams(conn->conn, query, 5, NULL, params, NULL, NULL, 0);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            ret = false;
            printf("res != PGRES_COMMAND_OK\n");
            printf("Error message: %s\n", PQerrorMessage(conn->conn));
        }
        if (res != NULL) {
            PQclear(res);
            res = NULL;
        }
        if (assortmentString)
            delete assortmentString;
    } else {
        char query[] =
            "INSERT INTO assortments (supplier_id, wholesale_price, delivery_terms, payment_terms)"
            "VALUES ($1, $2, $3, $4);";
        const char* params[4];
        std::string* assortmentString = assortment.getString();
        for (size_t i = 0; i < 4; i++)
            params[i] = assortmentString[i + 1].c_str();
        res = PQexecParams(conn->conn, query, 4, NULL, params, NULL, NULL, 1);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            ret = false;
            printf("res != PGRES_COMMAND_OK\n");
            printf("Error message: %s\n", PQerrorMessage(conn->conn));
        }
        if (res != NULL) {
            PQclear(res);
            res = NULL;
        }
        if (assortmentString)
            delete assortmentString;
    }
    return ret;
}

bool AssortmentMapper::remove(Assortment& assortment) {
    bool ret = true;
    PGresult* res = NULL;
    if (assortment.getId() != 0) {
        char query[100];
        snprintf(query, sizeof(query), "DELETE FROM assortments WHERE id = %u;", assortment.getId());
        res = PQexec(conn->conn, query);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            printf("res != PGRES_COMMAND_OK\n");
        }
    } else {
        ret = false;
    }
    return ret;
}