
#include "tree.h"

#include <cmath>
#include <iostream>
#include <strings.h>
#include <typeinfo>

#include "constants.h"
#include "parser.h"

using namespace std;

tree::tree(const string *input, const int input_len) {
    int i = 0;
    add_operator = new add();
    subtract_operator = new subtract();
    multiply_operator = new multiply();
    divide_operator = new divide();
    sinus_operator = new sinus();
    cosinus_operator = new cosinus();
    root = create_node(input, i, input_len);
}

tree::tree(tree &&other) noexcept {
    this->add_operator = other.add_operator;
    other.add_operator = NULL;
    this->subtract_operator = other.subtract_operator;
    other.subtract_operator = NULL;
    this->multiply_operator = other.multiply_operator;
    other.multiply_operator = NULL;
    this->divide_operator = other.divide_operator;
    other.divide_operator = NULL;
    this->sinus_operator = other.sinus_operator;
    other.sinus_operator = NULL;
    this->cosinus_operator = other.cosinus_operator;
    other.cosinus_operator = NULL;

    this->root = other.root;
    other.root = NULL;
}

tree::tree() {
    root = NULL;
    add_operator = new add();
    subtract_operator = new subtract();
    multiply_operator = new multiply();
    divide_operator = new divide();
    sinus_operator = new sinus();
    cosinus_operator = new cosinus();
}

tree::~tree() {
    delete root;
    delete add_operator;
    delete subtract_operator;
    delete multiply_operator;
    delete divide_operator;
    delete sinus_operator;
    delete cosinus_operator;
}

tree& tree::operator=(tree &&other) noexcept {
    if (this == &other) return *this;

    delete root;

    this->root = other.root;
    other.root = NULL;
    return *this;
}

void tree::print() const {
    if (root != NULL) print_node(root);
    cout << endl;
}

void tree::print_node(node *node) {
    if (typeid(*node) == typeid(number_node)) {
        cout << node->get_value() << " ";
    }
    else if (typeid(*node) == typeid(variable_node)) {
        cout << dynamic_cast<variable_node *>(node)->get_variable() << " ";
    }
    else if (typeid(*node) == typeid(operator_node)) {
        operator_node *node_cast = dynamic_cast<operator_node*>(node); // NOLINT(*-use-auto)
        cout << node_cast->get_operator_symbol() << " ";
        for (int i = 0; i < node_cast->get_children().size(); i++) print_node(node_cast->get_child(i));
    }
}

tree::node::node(tree *owner_tree) {
    this->owner_tree = owner_tree;
    this->value = DEFAULT_VALUE;
}

tree::number_node::number_node(tree *owner_tree, int value) : node(owner_tree){
    this->value = value;
}

tree::number_node::~number_node() = default;

tree::operator_node::operator_node(tree *owner_tree, const string &operator_symbol, node_evaluator *evaluator, const int &children_count, const string *input, int &i, const int &input_len) : node(owner_tree){
    this->children_count = children_count;
    this->operator_symbol = operator_symbol;
    this->evaluator = evaluator;
    this->value = DEFAULT_VALUE;
    for (int j = 0; j < children_count; j++) {
        i++;
        children.push_back(owner_tree->create_node(input, i, input_len));
    }
}

tree::operator_node::operator_node(tree *owner_tree, const string &operator_symbol, node_evaluator *evaluator, const int &children_count, const vector<node*> &children) : node(owner_tree) {
    this->children_count = children_count;
    this->operator_symbol = operator_symbol;
    this->evaluator = evaluator;
    this->value = DEFAULT_VALUE;
    this->children = children;
}

tree::operator_node::~operator_node() {
    for (int i = 0; i < children.size(); i++) delete children[i]; // NOLINT(*-loop-convert)
}

tree::node* tree::create_node(const string *input, int &i, const int &input_len) {
    if (i >= input_len) {
        cout << "Error: had to fix input" << endl;
        return new number_node(this, DEFAULT_FIX_TREE_VALUE);
    }

    string data = input[i];

    // first operators longer than one symbol
    if (data.length() > 1) {
        if (data == "sin") {
            return new operator_node(this, data, sinus_operator, 1, input, i, input_len);
        }
        if (data == "cos") {
            return new operator_node(this, data, cosinus_operator, 1, input, i, input_len);
        }
        if (parser::is_variable(data)) {
            return new variable_node(this, parser::variable_parse(data));
        }
        return new number_node(this, convert_string_to_int(data));
    }
    // now operator like + / - etc. and one character variables
    switch (data[0]) {
        case '+':
            return new operator_node(this, data, add_operator, 2, input, i, input_len);
        case '-':
            return new operator_node(this, data, subtract_operator, 2, input, i, input_len);
        case '*':
            return new operator_node(this, data, multiply_operator, 2, input, i, input_len);
        case '/':
            return new operator_node(this, data, divide_operator, 2, input, i, input_len);
        default:
            if ((65 <= static_cast<int>(data[0]) && static_cast<int>(data[0]) <= 90) || (97 <= static_cast<int>(data[0]) && static_cast<int>(data[0]) <= 122)) return new variable_node(this, data);
            return new number_node(this, convert_string_to_int(data));
    }
}

int tree::convert_string_to_int(const string &str) {
    int result = 0;
    for (int i = 0; i < str.length(); i++) {
        result *= 10;
        result += str[i] - '0';
    }
    return result;
}

int tree::node::get_value() const {
    return value;
}

string tree::operator_node::get_operator_symbol() {
    return operator_symbol;
}

tree::node *tree::operator_node::get_child(const int &idx) const {
    return children[idx];
}

tree::node *&tree::operator_node::get_child_ref(const int &idx) {
    return children[idx];
}

vector<tree::node*> tree::operator_node::get_children() {
    return children;
}

vector<tree::node *> & tree::operator_node::get_children_ref() {
    return children;
}

tree::node_evaluator *tree::operator_node::get_evaluator() const {
    return evaluator;
}

int tree::operator_node::get_children_count() const {
    return children_count;
}

tree::variable_node::variable_node(tree *owner_tree, const string &variable) : node(owner_tree){
    this->variable = variable;
}

tree::variable_node::~variable_node() {};

string tree::variable_node::get_variable() const {
    return variable;
}

void tree::print_variables() const {
    print_variables(root);
}

void tree::print_variables(node *node) {
    if (typeid(*node) == typeid(variable_node)) cout << dynamic_cast<variable_node *>(node)->get_variable() << " ";
    else if (typeid(*node) == typeid(operator_node)) {
        operator_node *node_cast = dynamic_cast<operator_node*>(node); // NOLINT(*-use-auto)
        for (int i = 0; i < node_cast->get_children().size(); i++) print_variables(node_cast->get_child(i));
    }
}

int tree::compile(string *input, int input_len) const {
    int i = 0;
    define_variable(root, input, i, input_len);
    define_variable(root, input, i, input_len);
    if (i > input_len) return 0;
    root->set_value(compile_node(root));
    return root->get_value();
}

tree tree::operator+(const tree &other) const {
    tree result = tree();
    result = *this;
    tree *other_copy = new tree();
    *other_copy = other;
    result.join(other_copy);
    delete other_copy;
    return std::move(result);
}

tree tree::operator=(const tree &other) {
    if (this == &other) {
        return std::move(*this);
    }
    delete root;
    this->root = copy_node(this, other.root);
    return std::move(*this);
}

tree::tree(const tree &other) {
    add_operator = new add();
    subtract_operator = new subtract();
    multiply_operator = new multiply();
    divide_operator = new divide();
    sinus_operator = new sinus();
    cosinus_operator = new cosinus();
    root = copy_node(this, other.root);
}


int tree::compile_node(node *node) {
    if (typeid(*node) == typeid(number_node)) return node->get_value();
    if (typeid(*node) == typeid(variable_node)) return node->get_value();
    if (typeid(*node) == typeid(operator_node)) {
        operator_node *node_cast = dynamic_cast<operator_node*>(node); // NOLINT(*-use-auto)
        for (int i = 0; i < node_cast->get_children().size(); i++) compile_node(node_cast->get_child(i));
        node_cast->set_value(node_cast->get_evaluator()->evaluate(node_cast->get_children_ref()));
        return node->get_value();
    };
    return 0;
}

void tree::define_variable(node *node, string *input, int &i, int &input_len) {
    if (typeid(*node) == typeid(variable_node)) {
        if (i >= input_len) {
            cout << "Error: Input too short" << endl;
            i++;
        }
        else {
            node->set_value(convert_string_to_int(input[i]));
            i++;
        }
    }
    else if (typeid(*node) == typeid(operator_node)) {
        operator_node *node_cast = dynamic_cast<operator_node*>(node); // NOLINT(*-use-auto)
        for (int j = 0; i < node_cast->get_children().size(); j++) define_variable(node_cast->get_child(j), input, i, input_len);
    }
}

void tree::node::set_value(const int &new_value) {
    this->value = new_value;
}

// evaluator functions
int tree::add::evaluate(vector<node*> &children) {
    int result = 0;
    for (int i = 0; i < children.size(); i++) result += children[i]->get_value(); // NOLINT(*-loop-convert)
    return result;
}

int tree::subtract::evaluate(vector<node*> &children) {
    if (!children.empty()) {
        int result = children[0]->get_value();
        for (int i = 1; i < children.size(); i++) result -= children[i]->get_value(); // NOLINT(*-loop-convert)
        return result;
    }
    return 0;
}

int tree::multiply::evaluate(vector<node*> &children) {
    int result = 1;
    for (int i = 0; i < children.size(); i++) result *= children[i]->get_value(); // NOLINT(*-loop-convert)
    return result;
}

int tree::divide::evaluate(vector<node*> &children) {
    if (!children.empty()) {
        int result = children[0]->get_value();
        for (int i = 1; i < children.size(); i++) result /= children[i]->get_value(); // NOLINT(*-loop-convert)
        return result;
    }
    return 0;
}

int tree::sinus::evaluate(vector<node*> &children) {
    if (children.size() == 1) return static_cast<int>(sin(children[0]->get_value()));
    return 0;
}

int tree::cosinus::evaluate(vector<node*> &children) {
    if (children.size() == 1) return static_cast<int>(cos(children[0]->get_value()));
    return 0;
}

tree::add::~add() {};
tree::subtract::~subtract() {};
tree::multiply::~multiply() {};
tree::divide::~divide() {};
tree::sinus::~sinus() {};
tree::cosinus::~cosinus() {};

//

void tree::join(tree *other) {
    join(other, root);
}

void tree::join(tree *other, node *&node) {
    if (typeid(*node) == typeid(variable_node) || typeid(*node) == typeid(number_node)) {
        delete node;
        node = copy_node(this, other->root);
    }
    else if (typeid(*node) == typeid(operator_node)) {
        join(other, dynamic_cast<operator_node*>(node)->get_child_ref(0));
    }
}

tree::node *tree::copy_node(tree *tree_owner, node *other) {
    if (typeid(*other) == typeid(number_node)) return new number_node(tree_owner, other->get_value());
    if (typeid(*other) == typeid(variable_node)) return new variable_node(tree_owner, dynamic_cast<variable_node*>(other)->get_variable());
    if (typeid(*other) == typeid(operator_node)) {
        operator_node *node_cast = dynamic_cast<operator_node*>(other); // NOLINT(*-use-auto)
        vector<node*> children_copy;
        for (int i = 0; node_cast->get_children().size() > i; i++) {
            children_copy.push_back(copy_node(tree_owner, node_cast->get_child(i)));
        }
        return new operator_node(tree_owner, node_cast->get_operator_symbol(), node_cast->get_evaluator(), node_cast->get_children_count(), children_copy);
    }
    return NULL;
}