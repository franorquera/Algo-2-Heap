#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/
int charcmp(const void* a, const void* b){
    char* a_aux = (char*)a;
    char* b_aux = (char*)b;
    return strcmp(a_aux, b_aux);
}

int numcmp(const void* a, const void* b){
    if(*(int*)a>*(int*)b) return 1;
    if(*(int*)a<*(int*)b) return -1;
    return 0;
}
static void prueba_crear_heap_vacio() {
    heap_t* heap = heap_crear(charcmp);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener clave A, es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap borrar clave A, es NULL, no existe", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_insertar(void) {
    heap_t *heap = heap_crear(charcmp);
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
    heap_t *heap = heap_crear(charcmp);

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


static void prueba_heap_desde_arreglo(){
    int nums_ordenados[8] = {9,8,7,5,4,4,3,2};

    int nums[8] = {4,2,7,9,4,3,8,5};
    void* arreglo[8] = { 0 };
    
    for(int i = 0; i< 8; i++){
        arreglo[i] = &nums[i];
    }
    heap_t* heap = heap_crear_arr(arreglo,8,numcmp);
    

    bool ok = true;

    for(int i = 0; i<8; i++){
        void* desencolado = heap_desencolar(heap);
        if(*(int*)desencolado != nums_ordenados[i]){
            ok = false;
            break;
        }

    }
    print_test("Prueba heap crear heap desde arreglo y desencolar los elementos", ok);
    heap_destruir(heap, NULL);

}

static void prueba_ordenar_arreglo(){
    int nums_ordenados[8] = {10,6,5,4,1,2};
    int nums[6] = {6,1,5,4,10,2};
    void* arreglo[6] = { 0 };
    
    for(int i = 0; i< 6; i++){
        arreglo[i] = &nums[i];
    }

    heap_sort(arreglo, 6,numcmp);
    bool ok = true;

    for(int i = 0; i<6; i++){
        if(*(int*)arreglo[i] != nums_ordenados[i]){
            ok = false;
            break;
        }

    }
    print_test("Prueba heap crear heap desde arreglo y desencolar los elementos", ok);
}





/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_heap_estudiante() {
    prueba_crear_heap_vacio();
    prueba_heap_insertar();
    prueba_heap_destruir_vectores();
    prueba_heap_desde_arreglo();
    prueba_ordenar_arreglo();
}