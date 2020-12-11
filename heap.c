#include "heap.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#define TAMANIO 10
#define NUEVO_TAM 2
#define DISMUNUIR_TAM 4

struct heap {
    void **datos;
    size_t tam;
    size_t cant;
    cmp_func_t cmp;
};


heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));

    if (!heap) return NULL;

    heap->datos = malloc(TAMANIO * sizeof(void*));
    
    if (!heap->datos) {
        free(heap);
        return NULL;
    }

    heap->tam = TAMANIO;
    heap->cant = 0;
    heap->cmp = cmp;
    return heap;
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cant == 0;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

void swap(int *x, int *y) {
   int k = *x;
   *x = *y;
   *y = k;
}

void upheap(void** datos, size_t cant, cmp_func_t cmp) {
    if (cant == 0) return;

    size_t pos = (cant - 1) / 2; 
    void* padre = datos[pos];
    if (cmp(padre, datos[cant]) < 0) {
        swap(padre, datos[cant]);
        upheap(datos, pos, cmp); 
    }
    return;
}

bool redimensionar(heap_t *heap, size_t nuevo_tam) {
   void* nuevos_datos = realloc(heap->datos, nuevo_tam * sizeof(void*));

   if (!nuevo_tam) return false;

   heap->datos = nuevos_datos;
   heap->tam = nuevo_tam;
   return true;
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (!elem) return false;

    if (heap->cant == heap->tam) {
        size_t nuevo_tam = NUEVO_TAM * heap->tam;
        if (!redimensionar(heap, nuevo_tam)) return false;
    }

    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->cmp);
    heap->cant++;
    return true;
}

void downheap(void** datos, size_t cant, cmp_func_t cmp);

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;

    if (heap->tam > TAMANIO && heap->cant * DISMUNUIR_TAM <= heap->tam) {
        size_t nuevo_tam = heap->tam / NUEVO_TAM;
        if (!redimensionar(heap, nuevo_tam)) return NULL;
    }

    swap(heap->datos[0], heap->datos[heap->cant - 1]);
    void* devolver = heap->datos[heap->cant - 1];
    downheap(heap->datos, 0, heap->cmp);
    heap->cant--;
    return devolver;
}