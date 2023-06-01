#include <iostream>
#include "BST.hpp"

int main(void)
{
  BST<int> bst;
  bst.add(6);
  bst.add(4);
  bst.add(2);
  bst.add(5);
  bst.add(9);
  bst.add(8);
  bst.add(10);

  bst.preorder();
  bst.inorder();
  bst.postorder();
  return 0;
}
