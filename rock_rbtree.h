#ifndef _ROCK_RBTREE_H
#define _ROCK_RBTREE_H



typedef struct rock_rbtree_node_s  rock_rbtree_node_t;

struct rock_rbtree_node_s {
    unsigned int       key;
    rock_rbtree_node_t     *left;
    rock_rbtree_node_t     *right;
    rock_rbtree_node_t     *parent;
    unsigned char                 color;
    unsigned char                 data;
};


typedef struct rock_rbtree_s  rock_rbtree_t;

typedef void (*rock_rbtree_insert_pt) (rock_rbtree_node_t *root,
    rock_rbtree_node_t *node, rock_rbtree_node_t *sentinel);

struct rock_rbtree_s {
    rock_rbtree_node_t     *root;
    rock_rbtree_node_t     *sentinel;
    rock_rbtree_insert_pt   insert;
};


#define rock_rbtree_init(tree, s, i)            \
    rock_rbtree_sentinel_init(s);               \
    (tree)->root = s;                         \
    (tree)->sentinel = s;                     \
    (tree)->insert = i


void rock_rbtree_insert(volatile rock_rbtree_t *tree,
    rock_rbtree_node_t *node);
void rock_rbtree_delete(volatile rock_rbtree_t *tree,
    rock_rbtree_node_t *node);
void rock_rbtree_insert_value(rock_rbtree_node_t *root, rock_rbtree_node_t *node,
    rock_rbtree_node_t *sentinel);
void rock_rbtree_insert_timer_value(rock_rbtree_node_t *root,
    rock_rbtree_node_t *node, rock_rbtree_node_t *sentinel);


#define rock_rbt_red(node)               ((node)->color = 1)
#define rock_rbt_black(node)             ((node)->color = 0)
#define rock_rbt_is_red(node)            ((node)->color)
#define rock_rbt_is_black(node)          (!rock_rbt_is_red(node))
#define rock_rbt_copy_color(n1, n2)      (n1->color = n2->color)


/* a sentinel must be black */

#define rock_rbtree_sentinel_init(node)  rock_rbt_black(node)


static inline rock_rbtree_node_t *
rock_rbtree_min(rock_rbtree_node_t *node, rock_rbtree_node_t *sentinel)
{
    while (node->left != sentinel) {
        node = node->left;
    }

    return node;
}







#endif