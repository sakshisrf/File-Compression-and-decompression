#include "node.h"

node::node(char character,int frequency){
    this->character=character;
    this->frequency=frequency;
    this->left=this->right=NULL;
}
node::node(char character){
    this->character=character;
}
char node::get_character() const{
    return character;
}
int node::get_frequency() const{
    return frequency;
}
node* node::get_left() const{
    return left;
}
node* node::get_right() const{
    return right;
}
void node::set_left(node* left){
    this->left=left;
}
void node::set_right(node* right){
    this->right=right;
}
