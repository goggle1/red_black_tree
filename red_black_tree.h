/******************************************************************************  
* red_black_tree.h                                                            *  
* Download From:                                                              *  
*    http://www.cs.tau.ac.il/~efif/courses/Software1_Summer_03/code/rbtree/   *  
* Last Edited by:                                                             *  
*    cheungmine                                                               *  
* 2010-8                                                                      *  
* Container class for a red-black tree: A binary tree that satisfies the      *  
* following properties:                                                       *  
* 1. Each node has a color, which is either red or black.                     *  
* 2. A red node cannot have a red parent.                                     *  
* 3. The number of black nodes from every path from the tree root to a leaf   *  
*    is the same for all tree leaves (it is called the 'black depth' of the   *  
*    tree).                                                                   *  
* Due to propeties 2-3, the depth of a red-black tree containing n nodes      *  
* is bounded by 2*log_2(n).                                                   *            
*                                                                             *  
* The red_black_tree_t template requires two template parmeters:              *  
* - The contained TYPE class represents the objects stored in the tree.       *  
*   It has to support the copy constructor and the assignment operator        *  
*   (operator=).                                                              *  
*                                                                             *  
* - pfcbRBTreeCompFunc is a functor used to define the order of objects of    *  
*   class TYPE:                                                               *  
*   This class has to support an operator() that recieves two objects from    *  
*   the TYPE class and returns a negative, zero or a positive integer,        *  
*   depending on the comparison result.                                       *  
******************************************************************************/  
#ifndef RED_BLACK_TREE_H   
#define RED_BLACK_TREE_H   
/*!  
 * Define RBTREE_SUPPORTS_MULTI_OBJECTS for supporting mapset (multi-key-map)  
 * if RBTREE_SUPPORTS_MULTI_OBJECTS defined, object must inherit from struct  
 * rbtree_object_base. That means the first member of object must be a struct  
 * pointer to next possible object if it has.  
 *  
 * #define  RBTREE_SUPPORTS_MULTI_OBJECTS  
 */  
#define  RBTREE_SUPPORTS_MULTI_OBJECTS   
#ifdef RBTREE_SUPPORTS_MULTI_OBJECTS   
    typedef struct _rbtree_object_base {   
        struct _rbtree_object_base *__next_object;   
    }rbtree_object_base;   
#endif   
/*! Color enumeration for nodes of red-black tree */  
typedef enum _red_black_color_enum    
{   
    rbcRed,    
    rbcBlack   
} red_black_color_enum;   
/*! Representation of a node in a red-black tree */  
typedef struct _red_black_node_t {   
    void                     * object;       /* the stored object user defined */  
    red_black_color_enum       color;        /* the color of the node */  
    struct _red_black_node_t * parent;       /* points to the parent node */  
    struct _red_black_node_t * right;        /* points to the right child */  
    struct _red_black_node_t * left;         /* points to the left child */  
} red_black_node_t;   
/*! Callback function prototype for comparing objects */  
typedef int (pfcbRBTreeCompFunc)(void *object1, void *object2);   
/*! Callback function prototype for traverse objects */  
typedef void(pfcbRBTreeOperFunc)(void *object,  void *param);   
     
/*! Construct of a red-black tree node  
 *  param object The object stored in the node  
 *  param color The color of the node  
 */  
extern red_black_node_t * rbnode_construct(void * object, red_black_color_enum color);   
/*! Recursive destructor for the entire sub-tree */  
extern void rbnode_destruct(red_black_node_t * node);   
/*! Calculate the depth of the sub-tree spanned by the given node  
 *  param node The sub-tree root  
 *  return The sub-tree depth  
 */  
extern int rbnode_depth(red_black_node_t * node);   
/*! Get the leftmost node in the sub-tree spanned by the given node  
 *  param node The sub-tree root  
 *  return The sub-tree minimum  
 */  
extern red_black_node_t * rbnode_minimum(red_black_node_t * node);   
/*! Get the rightmost node in the sub-tree spanned by the given node  
 *  param node The sub-tree root  
 *  return The sub-tree maximum  
 */  
extern red_black_node_t * rbnode_maximum(red_black_node_t * node);   
/*! Replace the object */  
extern void rbnode_replace(red_black_node_t * node, void * object);   
/*! Get the next node in the tree (according to the tree order)  
 *  param node The current node  
 *  return The successor node, or NULL if node is the tree maximum  
 */  
extern red_black_node_t * rbnode_successor(red_black_node_t * node);   
/*! Get the previous node in the tree (according to the tree order)  
 *  param node The current node  
 *  return The predecessor node, or NULL if node is the tree minimum  
 */  
extern red_black_node_t * rbnode_predecessor(red_black_node_t * node);   
/*! Duplicate the entire sub-tree rooted at the given node  
 *  param node The sub-tree root  
 *  return A pointer to the duplicated sub-tree root  
 */  
extern red_black_node_t * rbnode_duplicate(red_black_node_t * node);   
/*! Traverse a red-black sub-tree left first  
 *  param node The sub-tree root  
 *  param op The operation to perform on each object in the sub-tree  
 */  
extern void rbnode_traverse(red_black_node_t *node, pfcbRBTreeOperFunc *opFunc, void *param);   
/*! Traverse a red-black sub-tree right first  
 */  
extern void rbnode_traverse_right(red_black_node_t *node, pfcbRBTreeOperFunc *opFunc, void*param);   
/*! Representation of a red-black tree */  
typedef struct _red_black_tree_t {   
    red_black_node_t   * root;                /* pointer to the tree root */  
    int                  iSize;               /* number of objects stored */  
    pfcbRBTreeCompFunc * comp;                /* compare function */  
} red_black_tree_t;   
/*! Initialize a red-black tree with a comparision function  
 *  param tree The tree  
 *  param comp The comparision function  
 */  
void rbtree_init(red_black_tree_t * tree, pfcbRBTreeCompFunc * comp);   
/*! Construct a red-black tree with a comparison object  
 *  param comp A pointer to the comparison object to be used by the tree  
 *  return The newly constructed  tree  
 */  
red_black_tree_t * rbtree_construct(pfcbRBTreeCompFunc * comp);   
/*! Clean a red-black tree [takes O(n) operations]  
 *  param tree The tree  
 */  
extern void rbtree_clean(red_black_tree_t * tree);   
/*! Destruct a red-black tree  
 *  param tree The tree  
 */  
extern void rbtree_destruct(red_black_tree_t * tree);   
/*! Get the size of the tree [takes O(1) operations]  
 *  param tree The tree  
 *  return The number of objects stored in the tree  
 */  
extern int rbtree_size(red_black_tree_t * tree);   
/*! Get the depth of the tree [takes O(n) operations]  
 *  param tree The tree  
 *  return The length of the longest path from the root to a leaf node  
 */  
extern int rbtree_depth(red_black_tree_t * tree);   
/*! Check whether the tree contains an object [takes O(log n) operations]  
 *  param tree The tree  
 *  param object The query object  
 *  return (true) if an equal object is found in the tree, otherwise (false)  
 */  
extern int rbtree_contains(red_black_tree_t * tree, void * object);   
/*! Insert an object to the tree [takes O(log n) operations]  
 *  param tree The tree  
 *  param object The object to be inserted  
 *  return the inserted object node  
 */  
extern red_black_node_t * rbtree_insert(red_black_tree_t * tree, void * object);   
/*! Insert an unique object to the tree */  
extern red_black_node_t * rbtree_insert_unique(red_black_tree_t * tree, void * object);   
/*! Insert a new object to the tree as the a successor of a given node  
 *  param tree The tree  
 *  return The new node  
 */  
extern red_black_node_t * insert_successor_at(red_black_tree_t * tree,   
                                            red_black_node_t * at_node,   
                                            void * object);   
/*! Insert a new object to the tree as the a predecessor of a given node  
 *  param tree The tree  
 *  return The new node  
 */  
extern red_black_node_t * insert_predecessor_at(red_black_tree_t * tree,   
                                              red_black_node_t * at_node,   
                                              void * object);   
/*! Remove an object from the tree [takes O(log n) operations]  
 *  param tree The tree  
 *  param object The object to be removed  
 *  pre The object should be contained in the tree  
 */  
extern void rbtree_remove(red_black_tree_t * tree, void * object);   
/*! Get a handle to the tree minimum [takes O(log n) operations]  
 *  param tree The tree  
 *  return the minimal object in the tree, or a NULL if the tree is empty  
 */  
extern red_black_node_t * rbtree_minimum(red_black_tree_t * tree);   
/*! Get a handle to the tree maximum [takes O(log n) operations]  
 *  param tree The tree  
 *  return the maximal object in the tree, or a NULL if the tree is empty  
 */  
extern red_black_node_t * rbtree_maximum(red_black_tree_t * tree);   
/*! Get the next node in the tree (according to the tree order)  
 * [takes O(log n) operations at worst-case, but only O(1) amortized]  
 *  param tree The tree  
 *  param node The current object  
 *  return The successor node, or a NULL, if we are at the tree maximum  
 */  
extern red_black_node_t * rbtree_successor(red_black_tree_t * tree,   
                                           red_black_node_t * node);   
/*! Get the previous node in the tree (according to the tree order)  
 * [takes O(log n) operations at worst-case, but only O(1) amortized]  
 *  param tree The tree  
 *  param node The current object  
 *  return The predecessor node, or a NULL, if we are at the tree minimum  
 */  
extern red_black_node_t * rbtree_predecessor(red_black_tree_t * tree,   
                                             red_black_node_t * node);   
/*! Find a node that contains the given object  
 *  param tree The tree  
 *  param object The desired object  
 *  return A node that contains the given object, or NULL if no such object  
 * is found in the tree  
 */  
extern red_black_node_t * rbtree_find(red_black_tree_t * tree, void * object);   
/*! Remove the object stored in the given tree node   
 *  param tree The tree  
 *  param node The node storing the object to be removed from the tree  
 */  
extern void rbtree_remove_at(red_black_tree_t * tree, red_black_node_t * node);   
/*! Left-rotate the sub-tree spanned by the given node  
 *  param tree The tree  
 *  param node The sub-tree root  
 */  
extern void rbtree_rotate_left(red_black_tree_t * tree, red_black_node_t * node);   
/*! Right-rotate the sub-tree spanned by the given node  
 *  param tree The tree  
 *  param node The sub-tree root  
 */  
extern void rbtree_rotate_right(red_black_tree_t * tree, red_black_node_t * node);   
/*!  
 * Fix-up the red-black tree properties after an insertion operation  
 *  param tree The tree  
 *  param node The node that has just been inserted to the tree  
 *  pre The color of node must be red  
 */  
extern void rbtree_insert_fixup(red_black_tree_t * tree, red_black_node_t * node);   
/*! Fix-up the red-black tree properties after a removal operation  
 *  param tree The tree  
 *  param node The child of the node that has just been removed from the tree  
 */  
extern void rbtree_remove_fixup(red_black_tree_t * tree, red_black_node_t * node);   
/*! Traverse a red-black tree left first  
 *  param tree The tree  
 *  param op The operation to perform on every object of the tree (according to  
 * the tree order)  
 */  
extern void rbtree_traverse(red_black_tree_t * tree, pfcbRBTreeOperFunc * op, void *param);   
#define rbtree_traverse_left rbtree_traverse   
/*! Traverse a red-black tree right first */  
extern void rbtree_traverse_right(red_black_tree_t * tree, pfcbRBTreeOperFunc * op, void *param);   
#endif /* RED_BLACK_TREE_H */  

