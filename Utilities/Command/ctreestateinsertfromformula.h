#ifndef CTREESTATEINSERTFROMFORMULA_H
#define CTREESTATEINSERTFROMFORMULA_H

#include "icommand.h"
#include "Tree/treestate.h"

#include <QList>

class CTreeStateInsertFromFormula : public ICommand
{
public:
    /* Constructor */
    CTreeStateInsertFromFormula(TreeState* target, TreeNode* source) :
        tree(target),
        src(source) { text = "Insert from formula"; }

    /* Destructor */
    ~CTreeStateInsertFromFormula() {}

    bool execute();
    void undo();

    ICommand* copy() { return new CTreeStateInsertFromFormula(tree, src); }


private:
    TreeState* tree;
    TreeNode* src;

    TreeNode* parent;
    QList<TreeNode*> movedNodes;
};

#endif // CTREESTATEINSERTFROMFORMULA_H
