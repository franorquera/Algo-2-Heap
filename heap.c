#include "heap.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TAM 10
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

    heap->datos = malloc(TAM * sizeof(void*));
    
    if (!heap->datos) {
        free(heap);
        return NULL;
    }

    heap->tam = TAM;
    heap->cant = 0;
    heap->cmp = cmp;
    return heap;
}

size_t _posiscion_padre(size_t cant) {
    return (cant - 1) / 2; 
}

size_t _posiscion_hijo_izquierdo(size_t cant) {
    return cant * 2 + 1;
}

size_t _posiscion_hijo_derecho(size_t cant) {
    return cant * 2 + 2;
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


void _swap(int *x, int *y) {
   int k = *x;
   *x = *y;
   *y = k;
}

void upheap(void** datos, size_t cant, cmp_func_t cmp) {
    if (cant == 0) return;

    size_t pos_padre = _posiscion_padre(cant);
    void* padre = datos[pos_padre];
    if (cmp(padre, datos[cant]) < 0) {
        datos[pos_padre] = datos[cant];
        datos[cant] = padre;
        //_swap(padre, datos[cant]);
        upheap(datos, pos_padre, cmp); 
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

void downheap(void** datos, size_t pos_act, cmp_func_t cmp, size_t cant) {
    if (pos_act >= cant) return;

    size_t pos_hijo_izq = _posiscion_hijo_izquierdo(pos_act);
    size_t pos_hijo_der = _posiscion_hijo_derecho(pos_act);

    size_t pos_mayor = pos_act; // es 0
    void* padre = datos[pos_mayor];

    if (pos_hijo_izq < cant) {
        void* hijo_izq = datos[pos_hijo_izq];
        if (cmp(padre, hijo_izq) < 0) pos_mayor = pos_hijo_izq;
    }

    if (pos_hijo_der < cant) {
        void* hijo_der = datos[pos_hijo_der];
        if (cmp(padre, hijo_der) < 0) pos_mayor = pos_hijo_der;
    }

    // SI HAY UN SOLO ELEM NO ENTRA ACA
    if (pos_mayor != pos_act) {
        void* dato = datos[pos_mayor];
        datos[pos_mayor] = padre;
        padre = dato;

        //_swap(padre, datos[pos_mayor]);
        downheap(datos, pos_mayor, cmp, cant);
    }
}

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;

    if (heap->tam > TAM && heap->cant * DISMUNUIR_TAM <= heap->tam) {
        size_t nuevo_tam = heap->tam / NUEVO_TAM;
        if (!redimensionar(heap, nuevo_tam)) return NULL;
    }

    void* desencolado = heap->datos[0];
    heap->cant--;

    if (!heap_esta_vacio(heap)) {
        void* dato = heap->datos[0];
        heap->datos[0] = heap->datos[heap->cant];
        heap->datos[heap->cant] = dato;
        //_swap(heap->datos[0], heap->datos[heap->cant]);
        downheap(heap->datos, 0, heap->cmp, heap->cant);
    }
    return desencolado;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    while (!heap_esta_vacio(heap)) {
        if (destruir_elemento) destruir_elemento(heap->datos[heap->cant - 1]);
        heap->cant--;
    }
    free(heap->datos);
    free(heap);
}

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    heap_t* heap = heap_crear_arr(elementos, cant, cmp);
}


heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t* heap = heap_crear(cmp);

    for (int i = 0; i < n; i++) {
        heap_encolar(heap, arreglo[i]);
    }

    return heap;
}