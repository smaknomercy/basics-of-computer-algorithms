// https://leetcode.com/problems/implement-stack-using-queues/

typedef struct {
	int *arr;
	int top;
} MyStack;


MyStack* myStackCreate() {
	MyStack *obj=(MyStack*)malloc(sizeof(MyStack));
	obj->arr=(int*)malloc(sizeof(int)*100);
	obj->top=-1;
	return obj;
}

void myStackPush(MyStack* obj, int x) {
  obj->arr[++obj->top]=x;
}

int myStackPop(MyStack* obj) {
  return obj->arr[obj->top--];
}

int myStackTop(MyStack* obj) {
  return obj->arr[obj->top];
}

bool myStackEmpty(MyStack* obj) {
  return obj->top==-1;
}

void myStackFree(MyStack* obj) {
	free(obj->arr);
	free(obj);
}