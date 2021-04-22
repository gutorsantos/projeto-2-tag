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

    Professor* professor_list = create_list_professor();
    School* school_list = create_list_school();

    // Le os dados do arquivo e adiciona ao grafo
    FILE* file = readFile();
    while (fgets(line, sizeof(line), file)) {
        int prof_id = 0, school_id = 0, qualification = 0;
        int schools[4] = {0, 0, 0, 0};
        int requirements[2] = {0, 0};
        if( line_counter > 2 && line_counter < 103) {
            sscanf(line, "(P%d, %d): (E%d, E%d, E%d, E%d)", &prof_id, &qualification, &schools[0], &schools[1], &schools[2], &schools[3]);
            //printf("%d %d %d %d %d %d\n", prof_id, qualification, schools[0], schools[1], schools[2], schools[3]);
            professor_list = insert_professor(professor_list, prof_id, qualification, schools);
            
            for(int i = NUM_MAX_PREFERENCE-1; i >= 0; i--) {
                if(schools[i] != 0) {
                    add_edge(graph, prof_id, schools[i]);
                }
            }
        }else if(line_counter > 105 ){
            sscanf(line, "(E%d):(%d):(%d)", &school_id, &requirements[0], &requirements[1]);
            //printf("%d %d %d\n", school_id, requirements[0], requirements[1]);
            school_list = insert_school(school_list, school_id, requirements);
        }
        line_counter++;
    }
    closeFile(file);        // fecha o arquivo

    /* print_professor_list(professor_list);
    print_school_list(school_list);

    print_graph(graph, 'p');
    print_graph(graph, 'e');*/
    
    gale_shapley(graph, professor_list, school_list);

    //print_teste(school_list);
    destroy_graph(graph);
    destroy_professor(professor_list);
    destroy_school(school_list);
    return 0;
}