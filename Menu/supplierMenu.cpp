#include "menu.h"

void getAllSuppliers(DBConnection &dbConnection) {
    SupplierMapper suplierMapper = SupplierMapper(&dbConnection);
    std::vector<Supplier> suplierVector = suplierMapper.getAll();
    if (suplierVector.size() == 0) {
        std::cout << "No supplier is stored in the database" << std::endl;
        return;
    }
    std::cout << std::endl;
    for (auto i : suplierVector) {
        i.print();
    }
}

void addNewSuppliers(DBConnection &dbConnection) {
    SupplierMapper supplierMapper = SupplierMapper(&dbConnection);

    std::string name, postAddress, phoneNumber, faxNumber, email;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Input name: ";
    std::getline(std::cin, name);
    std::cout << "Input post address: ";
    std::getline(std::cin, postAddress);
    std::cout << "Input phone number: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Input fax number: ";
    std::getline(std::cin, faxNumber);
    std::cout << "Input email: ";
    std::getline(std::cin, email);

    Supplier supplier(name, postAddress, phoneNumber, faxNumber, email);

    if (supplierMapper.save(supplier)) {
        std::cout << "Supplier added successfully." << std::endl;
    } else {
        std::cout << "Failed to add supplier." << std::endl;
    }
}

void deleteSuppliers(DBConnection &dbConnection) {
    SupplierMapper supplierMapper = SupplierMapper(&dbConnection);

    std::string name;
    std::cout << "Input name of the supplier to delete: ";
    std::getline(std::cin, name);

    std::vector<Supplier> suppliers = supplierMapper.getByName(name);

    if (suppliers.empty()) {
        std::cout << "No suppliers found with that name." << std::endl;
    } else {
        std::cout << "Select the supplier to delete:" << std::endl;
        for (size_t i = 0; i < suppliers.size(); ++i) {
            std::cout << i + 1 << ") " << suppliers[i].getName() << std::endl;
        }

        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= suppliers.size()) {
            if (supplierMapper.remove(suppliers[choice - 1])) {
                std::cout << "Supplier removed successfully." << std::endl;
            } else {
                std::cout << "Failed to remove supplier." << std::endl;
            }
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void changeSupplier(DBConnection &dbConnection) {
    SupplierMapper supplierMapper = SupplierMapper(&dbConnection);

    std::string name;
    std::cout << "Input name of the supplier to change: ";
    std::cin >> name;

    std::vector<Supplier> suppliers = supplierMapper.getByName(name);

    if (suppliers.empty()) {
        std::cout << "No suppliers found with that name." << std::endl;
    } else {
        std::cout << "Select the supplier to change:" << std::endl;
        for (size_t i = 0; i < suppliers.size(); ++i) {
            std::cout << i + 1 << ") " << suppliers[i].getName() << std::endl;
        }

        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= suppliers.size()) {
            std::string postAddress, phoneNumber, faxNumber, email;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Input new post address: ";
            std::getline(std::cin, postAddress);
            std::cout << "Input new phone number: ";
            std::getline(std::cin, phoneNumber);
            std::cout << "Input new fax number: ";
            std::getline(std::cin, faxNumber);
            std::cout << "Input new email: ";
            std::getline(std::cin, email);

            suppliers[choice - 1].setPostAddress(postAddress);
            suppliers[choice - 1].setPhoneNumber(phoneNumber);
            suppliers[choice - 1].setFaxNumber(faxNumber);
            suppliers[choice - 1].setEmail(email);

            if (supplierMapper.save(suppliers[choice - 1])) {
                std::cout << "Supplier changed successfully." << std::endl;
            } else {
                std::cout << "Failed to change supplier." << std::endl;
            }
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void getSupplierAssortment(DBConnection &dbConnection) {
    SupplierMapper supplierMapper = SupplierMapper(&dbConnection);

    std::string name;
    std::cout << "Input name of the supplier to get assortment: ";
    std::cin >> name;

    std::vector<Supplier> suppliers = supplierMapper.getByName(name);

    if (suppliers.empty()) {
        std::cout << "No suppliers found with that name." << std::endl;
    } else {
        std::cout << "Select the supplier to get assortment:" << std::endl;
        for (size_t i = 0; i < suppliers.size(); ++i) {
            std::cout << i + 1 << ") " << suppliers[i].getName() << std::endl;
        }

        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= suppliers.size()) {
            AssortmentMapper assortmentMapper = AssortmentMapper(&dbConnection);
            std::vector<Assortment> assortment = assortmentMapper.getBySupplierName(suppliers[choice - 1].getName());

            if (!assortment.empty()) {
                std::cout << "Assortment for supplier '" << suppliers[choice - 1].getName() << "':" << std::endl;
                for (size_t i = 0; i < assortment.size(); ++i) {
                    assortment[i].print();
                }
            } else {
                std::cout << "No assortment found for supplier '" << suppliers[choice - 1].getName() << "'." << std::endl;
            }
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

void changeSupplierAssortment(DBConnection &dbConnection) {
    SupplierMapper supplierMapper = SupplierMapper(&dbConnection);

    std::string name;
    std::cout << "Input name of the supplier to change assortment: ";
    std::cin >> name;

    std::vector<Supplier> suppliers = supplierMapper.getByName(name);

    if (suppliers.empty()) {
        std::cout << "No suppliers found with that name." << std::endl;
    } else {
        std::cout << "Select the supplier to change assortment:" << std::endl;
        for (size_t i = 0; i < suppliers.size(); ++i) {
            std::cout << i + 1 << ") " << suppliers[i].getName() << std::endl;
        }

        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= suppliers.size()) {
            AssortmentMapper assortmentMapper = AssortmentMapper(&dbConnection);
            std::vector<Assortment> assortment = assortmentMapper.getBySupplierName(suppliers[choice - 1].getName());

            if (!assortment.empty()) {
                std::cout << "Select the assortment to change:" << std::endl;
                for (size_t i = 0; i < assortment.size(); ++i) {
                    assortment[i].print();
                }

                int assortmentChoice;
                std::cin >> assortmentChoice;

                if (assortmentChoice > 0 && assortmentChoice <= assortment.size()) {
                    double newWholesalePrice;
                    std::string newDeliveryTerms;
                    std::string newPaymentTerms;

                    // Запрос новых данных у пользователя
                    std::cout << "Enter new wholesale price: ";
                    std::cin >> newWholesalePrice;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter new delivery terms: ";
                    std::getline(std::cin, newDeliveryTerms);
                    std::cout << "Enter new payment terms: ";
                    std::getline(std::cin, newPaymentTerms);

                    // Создайте новый объект Assortment с обновленными данными
                    Assortment newAssortment(assortment[assortmentChoice - 1].getId(), newWholesalePrice, newDeliveryTerms, newPaymentTerms);

                    // Сохраните новый объект в базе данных
                    AssortmentMapper assortmentMapper = AssortmentMapper(&dbConnection);
                    bool updateSuccess = assortmentMapper.save(newAssortment);

                    if (updateSuccess) {
                        std::cout << "Assortment updated successfully." << std::endl;
                    } else {
                        std::cout << "Failed to update assortment." << std::endl;
                    }
                } else {
                    std::cout << "Invalid assortment choice." << std::endl;
                }
            } else {
                std::cout << "No assortment found for supplier '" << suppliers[choice - 1].getName() << "'." << std::endl;
            }
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
}