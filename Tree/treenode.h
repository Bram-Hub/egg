#ifndef TREE_TREENODE_H
#define TREE_TREENODE_H

#include <QList>
#include <QString>
#include <QQueue>

#include "Utilities/constants.h"

/*
 * A TreeNode is the basic node of an existential graph tree. These elements
 * can be one of four types: root, cut, statement, or placeholder.
 *
 * Out of these four, only the placeholder is allowed to change its type after
 * creation. The placeholder is special: calling one of the addChild functions
 * will simply replace the current TreeNode instead of creating a new node
 * further down the tree.
 *
 * Root and cut elements are allowed to have children of their own. These
 * are created and returned as the return value of the addChild set of
 * functions.
 *
 * Root elements do not have a parent, and there is only one root per graph
 * tree. Every other node in the tree extends from some branching off of the
 * root.
 *
 * TreeNodes are only allowed to have zero or one child placeholders at
 * any time. Placeholders are automatically leaves of the tree and may not
 * have placeholders of their own.
 */

class TreeNode
{
public:
    /* Constructor makes a root node */
    TreeNode()
        : type(constants::ELEMENT_ROOT)
        , depth(0)
        , name(QString("Root"))
        , parent()
        //, placeHolderChild()
        , numPlaceholderChildren(0)
        , myID(globalID++) {}

    /* Copy constructor */
    TreeNode(TreeNode *original);

    /* Destructor */
    ~TreeNode();

    /* Equality */
    static bool equals(TreeNode* node1, TreeNode* node2);
    static void getLeaves(TreeNode * root, QList<QList<QString> > &list,
                          QList<int> &cutCount, QList<int> &depths);
    void updateDepth();

    /* ID for debugging */
    static int globalID;
    int getID() { return myID; }

    /* Additions */
    TreeNode* addChildCut();
    TreeNode* addChildStatement(QString s);
    TreeNode* addChildPlaceholder();

    /* Move */
    static void move(TreeNode* node, TreeNode* targetParent);

    /* Detach */
    static void detach(TreeNode* node, TreeNode* parent);

    /* Text output in tree form */
    QString getTypeID();
    int getBoxWidth(int depth);
    QString getBoxLine(int depth, int end, bool bottom,
                       QString skips, TreeNode* highlighted,
                       QList<TreeNode*> selectionList);

    /* Pounce */
    void setPounceID(int target);
    int getPounceWidth(int depth);
    QString getPounceLine(int depth, int end, bool bottom,
                       QString skips, TreeNode* highlighted,
                       QList<TreeNode*> selectionList);

    /* Getters */
    QString getName() { return name; }
    //bool hasPlaceHolder() { return placeHolderChild; }
    bool hasAtLeastOnePlaceholder() { return numPlaceholderChildren >= 1; }
    int getNumPlaceholderChildren() { return numPlaceholderChildren; }
    int getType(){ return type; }
    QString getPounceID() { return pounceID; }
    int getDepth() {return depth;}

    /* TODO: fix rep. exposure (make private? friend TreeState?) */
    QList<TreeNode*> getChildren() { return children; }
    TreeNode* getParent() { return parent; }

    /* Boolean identifiers */
    bool isRoot() { return type == constants::ELEMENT_ROOT; }
    bool isCut() { return type == constants::ELEMENT_CUT; }
    bool isStatement(){ return type == constants::ELEMENT_STATEMENT; }
    bool isPlaceHolder() { return type == constants::ELEMENT_PLACEHOLDER; }
    bool isDetached() { return type != constants::ELEMENT_ROOT &&
                        parent == NULL; }


private:
    /* Constructor for non-root nodes */
    TreeNode(const int t, TreeNode* p, QString n)
            : type(t)
            , depth(p->getDepth()+1)
            , name(n)
            , parent(p)
            , numPlaceholderChildren(0)
            , myID(globalID++) {}

    /* Details */
    int type;
    int depth;
    QString name;

    /* Connections */
    TreeNode* parent;
    QList<TreeNode*> children;

    /* Placeholder */
    //bool placeHolderChild;
    int numPlaceholderChildren;

    /* New placeholder helpers */
    //void updatePlaceholderStatus();
    void addAfterPlaceholders(TreeNode* node);

    void removePlaceholder();

    /* ID's */
    QString pounceID;
    int myID;

};

#endif // TREE_TREENODE_H
