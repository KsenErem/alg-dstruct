#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_NUM_LENGTH 10

typedef struct node_t {
	int vertex;
	struct node_t* next;
} node_t;

typedef struct {
	node_t* front, * back;
} queue_t;

typedef struct {
	int* cont_verts;
	int cont_verts_count;
} vertex_t;

typedef struct {
	int verts_count;
	vertex_t* verts_array;
} graph_t;


int num_len(int num) {
	int k = 0;
	while (num > 0)
	{
		num /= 10;
		k++;
	}
	return k;
}

void free_graph(graph_t* graph) {
	for (int i = 0; i < graph->verts_count; i++)
		free(graph->verts_array[i].cont_verts);
	free(graph->verts_array);
	free(graph);
	return;
}

graph_t* get_graph(FILE* stream) {
	graph_t* our_graph = (graph_t*)malloc(sizeof(graph_t));
	if (!our_graph)
		return NULL;
	char* line_buf = (char*)malloc(MAX_NUM_LENGTH * sizeof(char)); 
	char* buf_iterator = NULL;
	fgets(line_buf, MAX_NUM_LENGTH, stream);
	if (!line_buf)
	{
		free(our_graph);
		return NULL;
	}
	our_graph->verts_count = atoi(line_buf);
	if (!our_graph->verts_count)
	{
		free_graph(our_graph);
		free(line_buf);
		return NULL;
	}
	int max_line_len = our_graph->verts_count * (num_len(our_graph->verts_count - 1) + 1) + 1;
	char* tmp = (char*)realloc(line_buf, sizeof(char) * max_line_len);
	if (!tmp)
	{
		free_graph(our_graph);
		free(line_buf);
		return NULL;
	}
	line_buf = tmp;
	our_graph->verts_array = (vertex_t*)malloc(sizeof(vertex_t) * our_graph->verts_count);
	if (!our_graph->verts_array)
	{
		free_graph(our_graph);
		free(line_buf);
		return NULL;
	}
	for (int k = 0; k < our_graph->verts_count; k++)
	{
		our_graph->verts_array[k].cont_verts_count = 0;
		our_graph->verts_array[k].cont_verts = (int*)malloc(1);
		if (!our_graph->verts_array[k].cont_verts)
		{
			free_graph(our_graph);
			free(line_buf);
			return NULL;
		}
	}
	int i, j;
	for (int k = 0; k < our_graph->verts_count; k++)
	{
		fgets(line_buf, max_line_len, stream);
		buf_iterator = line_buf;
		sscanf(buf_iterator, "%i", &i);
		buf_iterator += num_len(i) + 1;
		while (sscanf(buf_iterator, "%i", &j) > 0)
		{
			buf_iterator += num_len(j) + 1;
			our_graph->verts_array[i].cont_verts_count++;
			our_graph->verts_array[j].cont_verts_count++;
			int* tmp1 = (int*)realloc(our_graph->verts_array[i].cont_verts, sizeof(int) * our_graph->verts_array[i].cont_verts_count);
			int* tmp2 = (int*)realloc(our_graph->verts_array[j].cont_verts, sizeof(int) * our_graph->verts_array[j].cont_verts_count);
			if (!tmp1 || !tmp2)
			{
				if (tmp1)
					free(tmp1);
				free_graph(our_graph);
				free(buf_iterator);
				free(line_buf);
				return NULL;
			}
			our_graph->verts_array[i].cont_verts = tmp1;
			our_graph->verts_array[j].cont_verts = tmp2;
			our_graph->verts_array[i].cont_verts[our_graph->verts_array[i].cont_verts_count - 1] = j;
			our_graph->verts_array[j].cont_verts[our_graph->verts_array[j].cont_verts_count - 1] = i;
		}
	}
	free(line_buf);
	return our_graph;
}

queue_t* init_queue(void) {
	queue_t* q = (queue_t*)malloc(sizeof(queue_t));
	q->back = NULL;
	q->front = NULL;
	return q;
}

int is_empty(queue_t* queue) {
	return !queue->front ? TRUE : FALSE;
}

void push(queue_t* queue, int vertex) {
	node_t* element = (node_t*)malloc(sizeof(node_t));
	element->vertex = vertex;
	element->next = NULL;
	if (is_empty(queue))
	{
		queue->back = element;
		queue->front = element;
	}
	else
	{
		queue->back->next = element;
		queue->back = element;
	}
	return;
}

void pop(queue_t* queue) {
	node_t* to_free = queue->front;
	queue->front = queue->front->next;
	free(to_free);
	return;
}

int front(queue_t* queue) {
	return queue->front->vertex;
}

int BFS(FILE* stream, graph_t* graph) {
	if (!graph)
		return 0;
	queue_t* q = init_queue();
	if (!q)
	{
		free_graph(graph);
		return 0;
	}
	int* used = (int*)malloc(sizeof(int) * graph->verts_count);
	if (!used)
	{
		free_graph(graph);
		free(q);
		return 0;
	}
	push(q, 0);
	used[0] = TRUE;
	while (!is_empty(q))
	{
		fprintf(stream, "%i ", front(q));
		for (int i = 0; i < graph->verts_array[front(q)].cont_verts_count; i++)
		{
			if (used[graph->verts_array[front(q)].cont_verts[i]] != TRUE)
			{
				push(q, graph->verts_array[front(q)].cont_verts[i]);
				used[graph->verts_array[front(q)].cont_verts[i]] = TRUE;
			}
		}
		pop(q);
	}
	free_graph(graph);
	free(q);
	free(used);
	return 1;
}

int main() {
	graph_t* graph = get_graph(stdin);
	BFS(stdout, graph);
	return 0;
}