//
// Created by mkgrz on 12.11.2025.
//

#ifndef TEP_3_TREE_H
#define TEP_3_TREE_H
#include <string>
#include <vector>

using namespace std;

class tree {

    class node_evaluator;

    class node {
    protected:
        tree *owner_tree;
        int value;
    public:
        explicit node(tree *owner_tree);
        int get_value() const;
        void set_value(const int &value);
        virtual ~node() = default;
    };

    class number_node : public node {
    public:
        number_node(tree *owner_tree, int value);
        ~number_node() override;
    };

    class variable_node : public node {
        string variable;
    public:
        variable_node(tree *owner_tree, const string &variable);
        ~variable_node() override;
        string get_variable() const;
    };

    class operator_node : public node {
        int children_count;
        string operator_symbol;
        vector<node*> children;
        node_evaluator *evaluator;
    public:
        operator_node(tree *owner_tree, const string &operator_symbol, node_evaluator *evaluator, const int &children_count,const string *input, int &i, const int &input_len);
        operator_node(tree *owner_tree, const string &operator_symbol, node_evaluator *evaluator, const int &children_count, const vector<node*> &children);
        ~operator_node() override;
        string get_operator_symbol();
        node *get_child(const int &idx) const;
        node *&get_child_ref(const int &idx);
        vector<node*> get_children();
        vector<node*> &get_children_ref();
        node_evaluator *get_evaluator() const;
        int get_children_count() const;
    };

    class node_evaluator {
    public:
        virtual int evaluate(vector<node*> &children) = 0;
        virtual ~node_evaluator() = default;
    };

    class add : public node_evaluator {
        int evaluate(vector<node*> &children) override;
        ~add() override;
    };

    class subtract : public node_evaluator {
        int evaluate(vector<node*> &children) override;
        ~subtract() override;
    };

    class multiply : public node_evaluator {
        int evaluate(vector<node*> &children) override;
        ~multiply() override;
    };

    class divide : public node_evaluator {
        int evaluate(vector<node*> &children) override;
        ~divide() override;
    };

    class sinus : public node_evaluator {
        int evaluate(vector<node*> &children) override;
        ~sinus() override;
    };

    class cosinus : public node_evaluator {
        int evaluate(vector<node*> &children) override;
        ~cosinus() override;
    };

    node *root;

    node_evaluator *add_operator;
    node_evaluator *subtract_operator;
    node_evaluator *multiply_operator;
    node_evaluator *divide_operator;
    node_evaluator *sinus_operator;
    node_evaluator *cosinus_operator;

    static int convert_string_to_int(const string &str);

    static void print_variables(node *node);

    static void print_node(node *node);

    static void define_variable(node *node, string *input, int &i, int &input_len);

    void join(tree *other);

    void join(tree *other, node *&node);

    static node *copy_node(tree *tree_owner, node *node);

    static int compile_node(node *node);

public:
    node* create_node(const string *input, int &i, const int &input_len);

    tree();

    tree(const string *input, int input_len);

    tree(tree &&other) noexcept;

    ~tree();

    tree& operator=(tree &&other) noexcept;

    void print() const;

    void print_variables() const;

    int compile(string *input, int input_len) const;

    tree operator+(const tree &other) const;

    tree& operator=(const tree &other);

    tree(const tree &other);
};


#endif //TEP_3_TREE_H
