#ifndef LIST_H_
#define LIST_H_

#include "constants.h"
#include <string.h>

typedef struct Professor{
    int id;
    int qualification;
    int preferences[NUM_MAX_PREFERENCE];
    int is_hired;
    struct Professor *next;
} Professor;

typedef struct Vacancy {
    int qualification;
    int is_filled;
    int filled_by;
}Vacancy;

typedef struct School{
    int id;
    struct Vacancy* vacancies[NUM_MAX_VACANCY];
    struct School *next;
} School;

Professor* create_list_professor() {
    return NULL;
}

int is_professor_empty(Professor* p) {
    return p == NULL;
}

void print_professor_list(Professor* list) {
    printf("(codigo professor, habilitacoes): (Escolas em ordem decrescente de prioridade)\n");
    while(list != NULL) {
        printf("(P%d, %d): (E%d, E%d, E%d, E%d)\n", list->id, list->qualification, list->preferences[0], list->preferences[1], list->preferences[2], list->preferences[3]);
        list = list->next;
    }
}

Professor* create_professor(int id, int qualification, int preferences[]) {
    Professor* p = (Professor*) malloc(sizeof(Professor));
    p->id = id;
    p->qualification = qualification;
    p->is_hired = 0;
    memcpy(p->preferences, preferences, NUM_MAX_PREFERENCE*sizeof(int));
    p->next = NULL;

    return p;
}

Professor* find_professor(Professor* list, int id) {
    Professor* aux = list;
    while(aux != NULL) {
        if(aux->id == id) {
            return aux;
        }

        aux = aux->next;
    }
    return NULL;
}

Professor* insert_professor(Professor* list, int id, int qualification, int preferences[]) {
    Professor* new_prof = create_professor(id, qualification, preferences);
    if(is_professor_empty(list))
        return new_prof;

    Professor* aux = list;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = new_prof;
    // printf("Adicionado professor:");
    // printf("(P%d, %d): (E%d, E%d, E%d, E%d)\n", new_prof->id, new_prof->qualification, new_prof->preferences[0], new_prof->preferences[1], new_prof->preferences[2], new_prof->preferences[3]);
    return list;
}

void destroy_professor(Professor* p) {
    while(p != NULL) {
        Professor* aux = p->next;
        free(p);
        p = aux;
    }
}

int get_vacancy_qualification(Vacancy* v) {
    return v->qualification;
}

int is_vancancy_filled(Vacancy* v) {
    return v->is_filled;
}

int get_school_vacancies_length(School* s) {
    if(s->vacancies[1] != NULL) 
        return 2;
    else
        return 1;
}

int fill_vancancy(Vacancy* v, int prof_id) {
    v->is_filled = 1;
    v->filled_by = prof_id;
}

int vancancy_professor(Vacancy* v) {
    if(is_vancancy_filled(v)) {
        return 0;
    }else {
        return v->filled_by;
    }
}

Vacancy* create_vacancy(int q) {
    Vacancy* v = (Vacancy*) malloc(sizeof(Vacancy));
    v->qualification = q;
    v->is_filled = 0;
    v->filled_by = 0;
    return v;
}

School* create_list_school() {
    return NULL;
}

int is_school_empty(School* s) {
    return s == NULL;
}

void print_school_list(School* list) {
    printf("(codigo escola):(habilitacoes pretendidas):(habilitacoes pretendidas, se houver segunda vaga)\n");
    while(list != NULL) {
        printf("(E%d):(%d)", list->id, get_vacancy_qualification(list->vacancies[0]));
        if(get_school_vacancies_length(list) == 2) {
            printf(":(%d)\n", get_vacancy_qualification(list->vacancies[1]));
        } else printf("\n");
        list = list->next;
    }
}

School* create_school(int id, int requirements[]) {
    School* s = (School*) malloc(sizeof(School));
    s->id = id;
    for(int i = 0; i < NUM_MAX_VACANCY; i++) {
        if(requirements[i] != 0) {
            s->vacancies[i] = malloc(sizeof(Vacancy));
            s->vacancies[i] = create_vacancy(requirements[i]);
        }else {
            s->vacancies[i] = NULL;
        }
    }
    s->next = NULL;

    return s;
}
School* find_school(School* list, int id) {
    School* aux = list;
    while(aux != NULL) {
        if(aux->id == id) {
            return aux;
        }

        aux = aux->next;
    }
    return NULL;
}

int match_preferences(School* s, int preference) {
    int length = get_school_vacancies_length(s);
    for(int i = 0; i < length; i++) {
        if(!s->vacancies[i]->is_filled)
            return 1;
    }
    return 0;
}

School* insert_school(School* list, int id, int requirements[]) {
    School* new_school = create_school(id, requirements);
    if(is_school_empty(list))
        return new_school;
    
    School* aux = list;
    while(aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = new_school;

    /*printf("Adicionado escola:");
    printf("(E%d):(%d)", new_school->id, get_vacancy_qualification(new_school->vacancies[0]));
    if(get_school_vacancies_length(new_school) == 2) {
        printf(":(%d)\n", get_vacancy_qualification(new_school->vacancies[1]));
    } else printf("\n");*/

    return list;
}

void destroy_vacancy(Vacancy* v) {
    free(v);
}

void destroy_school(School* s) {
    while(s != NULL) {
        School* aux = s->next;
        for(int i = 0; i < get_school_vacancies_length(s); i++) {
            if(s->vacancies[i] != NULL)
                free(s->vacancies[i]);
        }
        free(s);
        s = aux;
    }
}

void print_teste(School* list) {
    while(list != NULL) {
        printf("Escola %d preenchida pelos professores\n\tP%d\n", list->id, list->vacancies[0]->filled_by);
        if(get_school_vacancies_length(list) == 2) {
            printf("\tP%d\n", list->vacancies[1]->filled_by);
        } else printf("\n");
        list = list->next;
    }
}

int size_professor(Professor* p) {
    if(p->preferences[3] != 0)
        return 4;
    else if(p->preferences[2] != 0)
        return 3;
    else if(p->preferences[3] != 0)
        return 2;
    else
        return 1;
}


#endif