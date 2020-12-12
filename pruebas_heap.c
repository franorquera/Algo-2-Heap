#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio() {
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener clave A, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap borrar clave A, es NULL, no existe", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_insertar(void) {
    heap_t *heap = heap_crear(strcmp);
    char* elem = "A"; 
    char* elem2 = "B";
    print_test("Prueba heap crear heap vacio", heap);
    print_test("La heap esta vacia", heap_esta_vacio(heap));
    print_test("No hay primer elemento", !heap_ver_max(heap));
    print_test("Encolo un elemento", heap_encolar(heap, &elem));
    print_test("La heap no esta vacia", heap_esta_vacio(heap) == false);
    print_test("Puedo ver el primer elemento", heap_ver_max(heap) == &elem);
    print_test("Encolo un segundo elemento", heap_encolar(heap, &elem2));
    print_test("Puedo ver el primer elemento", heap_ver_max(heap) == &elem2);
    print_test("Puedo desenheapr el primer elemento", heap_desencolar(heap) == &elem2);
    print_test("Puedo ver el nuevo primer elemento", heap_ver_max(heap) == &elem);
    print_test("Puedo desenheapr el nuevo primer elemento", heap_desencolar(heap) == &elem);
    print_test("No puedo desenheapr mas elementos", !heap_desencolar(heap));
    print_test("La heap esta vacia", heap_esta_vacio(heap));
    print_test("No hay primer elemento", !heap_ver_max(heap));
    heap_destruir(heap, NULL);
}

static void prueba_heap_destruir_vectores() {
    heap_t *heap = heap_crear(strcmp);

    char **elem;
    char **elem2;

    elem = malloc(10 * sizeof(char));
    elem2 = malloc(10 * sizeof(char));

    *elem = "A";
    *elem2 = "B";

    print_test("Prueba heap crear heap vacio", heap);
    print_test("La heap esta vacia", heap_esta_vacio(heap));
    print_test("Encolo un elemento", heap_encolar(heap, elem));
    print_test("Encolo un elemento", heap_encolar(heap, elem2));
    heap_destruir(heap, free);
}



/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_heap_estudiante() {
    prueba_crear_heap_vacio();
    prueba_heap_insertar();
    prueba_heap_destruir_vectores();
}