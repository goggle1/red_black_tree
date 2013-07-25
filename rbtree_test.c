//   
// rbtree_test.c   
// by cheungmine   
//   
#include <stdio.h>   
#include <stdlib.h>   
#include <assert.h>   
// RBTREE_SUPPORTS_MULTI_OBJECTS 在下面的文件中被定义，如果不想支持多图，注释掉它   
#include "red_black_tree.h"   
  
/*!  
 */  
int cmp_int(int a, int b)   
{   
  return (a > b) ? -1 : ((a == b) ? 0 : 1);   
}   
/*!  
 */  
void my_print(int value)   
{   
  printf("%d ", value);   
}   
#if !defined(RBTREE_SUPPORTS_MULTI_OBJECTS)   
void test_rbtree_insert_repeat()   
{   
    int i, n;   
       
    red_black_tree_t  tree;   
    red_black_node_t *node, *node2;   
    n = 20;   
    rbtree_init(&tree, (pfcbRBTreeCompFunc*) cmp_int);   
    for (i=0; i<n; i++){   
      rbtree_insert(&tree, (void*) i);   
    }   
    node = rbtree_find(&tree, (void*) 5);   
    assert(node);   
    node2 = rbtree_insert(&tree, (void*) 5);   
    assert(node2);   
    assert(node!=node2);   
    node = rbtree_find(&tree, (void*) 10);   
    assert(node);   
    node2 = rbtree_insert(&tree, (void*) 10);   
    assert(node2);   
    assert(node!=node2);   
    printf("n = %d, d = %d\n", n, rbtree_depth(&tree));   
    rbtree_traverse(&tree, (pfcbRBTreeOperFunc*) my_print);   
    printf("\n");   
    rbtree_traverse_right(&tree, (pfcbRBTreeOperFunc*) my_print);   
    printf("\n");   
    rbtree_clean(&tree);   
}   
#endif   
void test_rbtree_insert_unique()   
{   
    int i, n;   
       
    red_black_tree_t  tree;   
    red_black_node_t *node, *node2;   
    n = 20;   
    rbtree_init(&tree, (pfcbRBTreeCompFunc*) cmp_int);   
    for (i=0; i<n; i++){   
      rbtree_insert_unique(&tree, (void*) i);   
    }   
    node = rbtree_find(&tree, (void*) 5);   
    assert(node);   
    node2 = rbtree_insert_unique(&tree, (void*) 5);   
    assert(node2);   
    assert(node==node2);   
    node = rbtree_find(&tree, (void*) 10);   
    assert(node);   
    node2 = rbtree_insert_unique(&tree, (void*) 10);   
    assert(node2);   
    assert(node==node2);   
    printf("n = %d, d = %d\n", n, rbtree_depth(&tree));   
    rbtree_traverse(&tree, (pfcbRBTreeOperFunc*) my_print, 0);   
    printf("\n");   
    rbtree_traverse_right(&tree, (pfcbRBTreeOperFunc*) my_print, 0);   
    printf("\n");   
    rbtree_clean(&tree);   
}   
#ifdef RBTREE_SUPPORTS_MULTI_OBJECTS   
typedef struct _MYOBJECT   
{   
    struct _MYOBJECT *__next_object;   
    int  data;   
}MYOBJECT;   
int cmp_int_multimap(MYOBJECT *a, MYOBJECT *b)   
{   
  return (a->data > b->data) ? -1 : ((a->data == b->data) ? 0 : 1);   
}   
/*!  
 */  
void my_print_multimap(MYOBJECT *obj)   
{   
    while (obj) {   
        printf("%d ", obj->data);   
        obj = obj->__next_object;   
    }   
}   
void test_rbtree_insert_multimap()   
{   
    int i, n;   
    MYOBJECT *obj;   
    MYOBJECT **objects;   
    red_black_tree_t  tree;   
    red_black_node_t *node;   
    n = 20;   
    rbtree_init(&tree, (pfcbRBTreeCompFunc*) cmp_int_multimap);   
    objects = (MYOBJECT**) calloc(n, sizeof(MYOBJECT*));   
    for (i=0; i<n; i++){   
        obj = (MYOBJECT*) malloc(sizeof(MYOBJECT));   
        objects[i] = obj;   
        obj->__next_object = 0;  // MUST be NULL   
        obj->data = i;   
           
        rbtree_insert(&tree, (void*) obj);   
    }   
    rbtree_insert(&tree, (void*) objects[5]);   
    obj = (MYOBJECT*) malloc(sizeof(MYOBJECT));   
    obj->__next_object = 0;  // MUST be NULL   
    obj->data = 5;   
    rbtree_insert(&tree, (void*) obj);   
               
    printf("n = %d, d = %d\n", n, rbtree_depth(&tree));   
    printf("(");   
    node = rbtree_find(&tree, (void*) objects[5]);   
    if (node){   
        MYOBJECT *obj = node->object;   
        while (obj) {   
            printf("%d ", obj->data);   
            obj = obj->__next_object;   
        }   
    }   
    printf(")\n");   
    rbtree_traverse(&tree, (pfcbRBTreeOperFunc*) my_print_multimap, 0);   
    printf("\n");   
    rbtree_traverse_right(&tree, (pfcbRBTreeOperFunc*) my_print_multimap, 0);   
    printf("\n");   
    rbtree_clean(&tree);   
    for (i=0; i<n; i++){   
        free(objects[i]);   
    }   
    free(objects);   
    free(obj);   
}   
#endif // RBTREE_SUPPORTS_MULTI_OBJECTS   
int main(int argc, char * argv[])   
{   
#if !defined(RBTREE_SUPPORTS_MULTI_OBJECTS)   
    test_rbtree_insert_repeat();   
#endif   
    test_rbtree_insert_unique();   
    test_rbtree_insert_multimap();   
    return 0;   
}  

