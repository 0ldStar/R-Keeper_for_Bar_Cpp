"CREATE TABLE employees ("
"  id serial PRIMARY KEY,"
"  name text,"
"  address text,"
"  date_of_birth date,"
"  position text,"
"  salary numeric);"

"CREATE TABLE transfers ("
"  id serial PRIMARY KEY,"
"  employee_id integer,"
"  position text,"
"  reason text,"
"  number_of_order integer,"
"  date_of_order date);"

"CREATE TABLE drinks ("
"  id serial PRIMARY KEY,"
"  name text,"
"  portion_size integer,"
"  capacity capacity_enum);"

"CREATE TABLE ingredients ("
"  id serial PRIMARY KEY,"
"  product_id integer,"
"  quantity integer,"
"  unit_of_measurement text);"

"CREATE TABLE drinks_recipes ("
"  drink_id integer,"
"  ingredient_id integer,"
"  PRIMARY KEY (drink_id, ingredient_id));"

"CREATE TABLE snacks_recipes ("
"  snack_id integer,"
"  ingredient_id integer,"
"  PRIMARY KEY (snack_id, ingredient_id));"

"CREATE TABLE snacks ("
"  id serial PRIMARY KEY,"
"  name text,"
"  size_of_portions integer);"

"CREATE TABLE suppliers ("
"  id serial PRIMARY KEY,"
"  name text,"
"  post_address text,"
"  phone_number text,"
"  fax_number text,"
"  email text);"

"CREATE TABLE bank_details ("
"  id serial PRIMARY KEY,"
"  supplier_id integer,"
"  name text,"
"  city text,"
"  TIN text,"
"  settlement_account text);"

"CREATE TABLE assortments ("
"  id serial PRIMARY KEY,"
"  supplier_id integer,"
"  wholesale_price numeric,"
"  delivery_terms text,"
"  payment_terms text);"

"CREATE TABLE products ("
"  id serial PRIMARY KEY,"
"  name text);"

"CREATE TABLE product_assortment ("
"  assortment_id integer,"
"  product_id integer,"
"  PRIMARY KEY (assortment_id, product_id));"

"ALTER TABLE transfers ADD FOREIGN KEY (employee_id) REFERENCES employees (id);"
"ALTER TABLE drinks_recipes ADD FOREIGN KEY (drink_id) REFERENCES drinks (id);"
"ALTER TABLE snacks_recipes ADD FOREIGN KEY (snack_id) REFERENCES snacks (id);"
"ALTER TABLE drinks_recipes ADD FOREIGN KEY (ingredient_id) REFERENCES ingredients (id);"
"ALTER TABLE snacks_recipes ADD FOREIGN KEY (ingredient_id) REFERENCES ingredients (id);"
"ALTER TABLE ingredients ADD FOREIGN KEY (product_id) REFERENCES products (id);"
"ALTER TABLE product_assortment ADD FOREIGN KEY (product_id) REFERENCES products (id);"
"ALTER TABLE product_assortment ADD FOREIGN KEY (assortment_id) REFERENCES assortments (id);"
"ALTER TABLE bank_details ADD FOREIGN KEY (supplier_id) REFERENCES suppliers (id);"
"ALTER TABLE assortments ADD FOREIGN KEY (supplier_id) REFERENCES suppliers (id);"
