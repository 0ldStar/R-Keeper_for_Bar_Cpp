#include "Recipe.h"

Recipe::Recipe(unsigned id, int ingredient_id, RecipeType type) {
    this->id = id;
    this->ingredient_id = ingredient_id;
    this->type = type;
}

Recipe::Recipe(int ingredient_id, RecipeType type) {
    this->id = 0;
    this->ingredient_id = ingredient_id;
    this->type = type;
}

Recipe::~Recipe() {
}

std::string* Recipe::getString() {
    std::string* stringArray = new std::string[3];
    stringArray[0] = std::to_string(id);
    stringArray[1] = std::to_string(ingredient_id);
    return stringArray;
}

void Recipe::print() {
    std::cout << "Type: " << (type == DRINK ? "Drink" : "Snack") << " Ingredient ID: " << ingredient_id << std::endl;
}