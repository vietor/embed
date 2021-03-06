/*
 * Part of embed, a tiny C tools library.
 * Copyright 2014-2015, Vietor Liu <vietor.liu at gmail.com>
 * All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE or LICENSE.embed file.
 */

#ifndef RBTREE_H
#define RBTREE_H

#include "embed.h"

enum { RBCOLOR_BLACK, RBCOLOR_RED };

struct rbnode {
	struct rbnode *parent;
	struct rbnode *left;
	struct rbnode *right;
	unsigned long color;
};

struct rbtree {
	struct rbnode *root;
	EMBED_EXTERN int (*search) (const void*, const struct rbnode*);
	EMBED_EXTERN int (*compare) (const struct rbnode*, const struct rbnode*);
};

EMBED_EXTERN struct rbnode rbnode_null;

#define RBNODE_NULL  (&rbnode_null)
#define RBNODE_EMPTY ((void *)0)

#define rbtree_entry(ptr, type, member)		\
	container_of(ptr, type, member)

#define rbnode_entry(ptr, type, member)		\
	container_of(ptr, type, member)

static inline void rbtree_init(struct rbtree *rbtree,
			int (*search)(const void*, const struct rbnode*),
			int (*compare)(const struct rbnode*, const struct rbnode*))
{
	rbtree->root = RBNODE_NULL;
	rbtree->search = search;
	rbtree->compare = compare;
}

static inline int rbtree_empty(struct rbtree *rbtree)
{
	return rbtree->root == RBNODE_NULL;
}

static inline void rbnode_init(struct rbnode *rbnode)
{
	rbnode->parent = RBNODE_EMPTY;
	rbnode->left = RBNODE_EMPTY;
	rbnode->right = RBNODE_EMPTY;
	rbnode->color = RBCOLOR_BLACK;
}

static inline int rbnode_empty(struct rbnode *rbnode)
{
	return rbnode->parent == RBNODE_EMPTY;
}

EMBED_EXTERN void rbtree_delete(struct rbtree *rbtree, struct rbnode *data);

enum { RBINSERT_MULTI, RBINSERT_TRYONE, RBINSERT_REPLACE };

EMBED_EXTERN struct rbnode *rbtree_insert3(struct rbtree *rbtree, struct rbnode *data, int flag);

static inline void rbtree_insert(struct rbtree *rbtree, struct rbnode *data)
{
	rbtree_insert3(rbtree, data, RBINSERT_MULTI);
}

static inline struct rbnode *rbtree_insert_tryone(struct rbtree *rbtree, struct rbnode *data)
{
	return rbtree_insert3(rbtree, data, RBINSERT_TRYONE);
}

static inline struct rbnode *rbtree_insert_replace(struct rbtree *rbtree, struct rbnode *data)
{
	return rbtree_insert3(rbtree, data, RBINSERT_REPLACE);
}

EMBED_EXTERN struct rbnode *rbtree_first(struct rbtree *rbtree);
EMBED_EXTERN struct rbnode *rbtree_last(struct rbtree *rbtree);
EMBED_EXTERN struct rbnode *rbtree_next(struct rbnode *rbtree);
EMBED_EXTERN struct rbnode *rbtree_previous(struct rbnode *rbtree);
EMBED_EXTERN struct rbnode *rbtree_search (struct rbtree *rbtree, void *context);

#endif
