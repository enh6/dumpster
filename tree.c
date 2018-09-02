#include "test.h"
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
  char val;
  struct _Node *left;
  struct _Node *right;
} Node;

typedef Node *stack_element_t;
#include "stack.h"

typedef Node *queue_element_t;
#include "queue.h"

typedef void (*callback_t)(Node *node);

void pre_order_traversal(Node *root, callback_t callback) {
  if (!root)
    return;
  callback(root);
  pre_order_traversal(root->left, callback);
  pre_order_traversal(root->right, callback);
}

void pre_order_traversal_iterative(Node *root, callback_t callback) {
  Node *node = root;
  Stack s = stack_create();
  while (node || !stack_empty(s)) {
    while (node) {
      callback(node);
      stack_push(s, node);
      node = node->left;
    }
    node = stack_top(s);
    stack_pop(s);
    node = node->right;
  }
  stack_destroy(s);
}

void in_order_traversal(Node *root, callback_t callback) {
  if (!root)
    return;
  in_order_traversal(root->left, callback);
  callback(root);
  in_order_traversal(root->right, callback);
}

void in_order_traversal_iterative(Node *root, callback_t callback) {
  Node *node = root;
  Stack s = stack_create();
  while (node || !stack_empty(s)) {
    while (node) {
      stack_push(s, node);
      node = node->left;
    }
    node = stack_top(s);
    stack_pop(s);
    callback(node);
    node = node->right;
  }
  stack_destroy(s);
}

void post_order_traversal(Node *root, callback_t callback) {
  if (!root)
    return;
  post_order_traversal(root->left, callback);
  post_order_traversal(root->right, callback);
  callback(root);
}

void post_order_traversal_iterative(Node *root, callback_t callback) {
  if (!root)
    return;
  Stack s = stack_create();
  Node *cur, *pre = NULL;
  stack_push(s, root);
  while (!stack_empty(s)) {
    cur = stack_top(s);
    if ((!cur->left && !cur->right) ||
        (pre && (pre == cur->left || pre == cur->right))) {
      callback(cur);
      stack_pop(s);
      pre = cur;
    } else {
      if (cur->right)
        stack_push(s, cur->right);
      if (cur->left)
        stack_push(s, cur->left);
    }
  }
  stack_destroy(s);
}

void level_order_traversal(Node *root, callback_t callback) {
  if (!root)
    return;
  Queue q = queue_create();
  queue_enqueue(q, root);
  while (!queue_empty(q)) {
    Node *node = queue_dequeue(q);
    callback(node);
    if (node->left)
      queue_enqueue(q, node->left);
    if (node->right)
      queue_enqueue(q, node->right);
  }
  queue_destroy(q);
}

/********************************
  Test tree traversal functions
********************************/

char *result;
int idx, cnt;

void test_val(Node *node) {
  ASSERT(node->val == result[idx]);
  idx++;
}

typedef void (*traversal_t)(Node *root, callback_t callback);

Node *build_tree() {
  Node *root = malloc(sizeof(Node) * 9);
  memset(root, 0, sizeof(Node) * 9);
  for (int i = 0; i < 9; i++)
    root[i].val = '0' + i;
  root[0].left = &root[1];
  root[0].right = &root[2];
  root[1].left = &root[3];
  root[1].right = &root[4];
  root[2].right = &root[5];
  root[4].left = &root[6];
  root[4].right = &root[7];
  root[5].left = &root[8];
  return root;
}

int main() {
  TEST_CASE(pre_order) {
    Node *root = build_tree();
    result = "013467258";
    cnt = 9;
    idx = 0;
    pre_order_traversal(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(pre_order_iterative) {
    Node *root = build_tree();
    result = "013467258";
    cnt = 9;
    idx = 0;
    pre_order_traversal_iterative(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(in_order) {
    Node *root = build_tree();
    result = "316470285";
    cnt = 9;
    idx = 0;
    in_order_traversal(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(in_order_iterative) {
    Node *root = build_tree();
    result = "316470285";
    cnt = 9;
    idx = 0;
    in_order_traversal_iterative(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(post_order) {
    Node *root = build_tree();
    result = "367418520";
    cnt = 9;
    idx = 0;
    post_order_traversal(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(post_order_iterative) {
    Node *root = build_tree();
    result = "367418520";
    cnt = 9;
    idx = 0;
    post_order_traversal_iterative(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(level_order) {
    Node *root = build_tree();
    result = "012345678";
    cnt = 9;
    idx = 0;
    level_order_traversal(root, test_val);
    ASSERT(cnt == idx);
  }
  TEST_CASE(stack) {
    Stack s = stack_create();
    Node *idx = 0;
    stack_push(s, idx++);
    stack_push(s, idx++);
    stack_push(s, idx++);
    ASSERT(stack_top(s) == idx - 1);
    stack_pop(s);
    stack_push(s, idx++);
    stack_push(s, idx++);
    stack_push(s, idx++);
    ASSERT(stack_top(s) == idx - 1);
    stack_pop(s);
    stack_push(s, idx++);
    stack_push(s, idx++);
    stack_push(s, idx++);
    stack_push(s, idx++);
    ASSERT(stack_top(s) == idx - 1);
    stack_pop(s);
    stack_push(s, idx++);
    stack_push(s, idx++);
    stack_push(s, idx++);
    ASSERT(stack_top(s) == idx - 1);
    stack_pop(s);
    stack_push(s, idx++);
    stack_push(s, idx++);
    ASSERT(stack_top(s) == idx - 1);
    stack_pop(s);
    stack_push(s, idx++);
    stack_push(s, idx++);
    stack_push(s, idx++);
    ASSERT(stack_top(s) == idx - 1);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    stack_pop(s);
    ASSERT(stack_empty(s));
    stack_destroy(s);
  }
  TEST_CASE(queue) {
    Queue q = queue_create();
    Node *idx = 0, *idx2 = 0;
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    queue_enqueue(q, idx++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_dequeue(q) == idx2++);
    ASSERT(queue_empty(q));
    queue_destroy(q);
  }
  TEST_END();
  return 0;
}
