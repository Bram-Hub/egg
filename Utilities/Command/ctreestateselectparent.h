#ifndef CTREESTATESELECTPARENT_H
#define CTREESTATESELECTPARENT_H

#include "Tree/treestate.h"
#include "Tree/treenode.h"

/*
 * This command will call the select parent function on a tree state
 */
class CTreeStateSelectParent : public ICommand
{
public:
    /* Constructor */
    CTreeStateSelectParent(TreeState* t) :
        tree(t) { text = "Select parent"; }

    /* Destructor */
    ~CTreeStateSelectParent() {}

    bool execute();
    void undo();
    void redo();

    ICommand* copy();

private:
    TreeState* tree;
    TreeNode* previous;
};

#endif // CTREESTATESELECTPARENT_H
