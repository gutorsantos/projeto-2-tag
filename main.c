/** Projeto 2 - TAG TA
 * Autor: Gustavo Rodrigues dos Santos 
 * Matricula: 19/0014121
 * Materia: Teoria e Aplicaçao de Grafos - Turma A
 * Ano: 2020 - 2o semestre 
 * Data: 29/04/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph.h"
#include "file.h"
#include "list.h"
#include "matching.h"


int main() {
    Graph* graph = create_graph(NUM_PROFS, NUM_SCHOOLS);

    char line[256];
    int line_counter = 0;

    Professor professor_list[NUM_PROFS];
    memset(professor_list, 0, sizeof(professor_list));
    School school_list[NUM_SCHOOLS];
    memset(school_list, 0, sizeof(school_list));

    // Le os dados do arquivo e adiciona ao grafo
    FILE* file = readFile();
    while (fgets(line, sizeof(line), file)) {
        int prof_id = 0, school_id = 0, qualification = 0;
        int schools[4] = {0, 0, 0, 0};
        int requirements[2] = {0, 0};
        if( line_counter > 2 && line_counter < 103) {
            sscanf(line, "(P%d, %d): (E%d, E%d, E%d, E%d)", &prof_id, &qualification, &schools[0], &schools[1], &schools[2], &schools[3]);
            //printf("%d %d %d %d %d %d\n", prof_id, qualification, schools[0], schools[1], schools[2], schools[3]);
            professor_list[prof_id] = insert_professor(prof_id, qualification, schools);
            
            for(int i = NUM_MAX_PREFERENCE-1; i >= 0; i--) {
                if(schools[i] != 0) {
                    add_edge(graph, prof_id, schools[i]);
                }
            }
        }else if(line_counter > 105 ){
            sscanf(line, "(E%d):(%d):(%d)", &school_id, &requirements[0], &requirements[1]);
            //printf("%d %d %d\n", school_id, requirements[0], requirements[1]);
            school_list[school_id] = insert_school(school_id, requirements);
        }
        line_counter++;
    }
    closeFile(file);        // fecha o arquivo*/

    Professor teste[NUM_PROFS];
    memcpy(teste, professor_list, NUM_PROFS*sizeof(Professor));
    // PRINT GRAPH
    // print_graph(graph, 'p');
    // print_graph(graph, 'e');
    gale_shapley(graph, teste, school_list);
    printf("alo");
    for(int i = 1; i < NUM_PROFS; i++) {
        if(teste[i].is_hired == 0) {
            memcpy(teste[i].preferences, professor_list[i].preferences, NUM_PROFS*sizeof(Professor));
            
        }
    }
    gale_shapley(graph, teste, school_list);
    print_matching(school_list, teste);

    destroy_graph(graph);
    return 0;
}