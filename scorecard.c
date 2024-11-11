#include <stdio.h>
#include <string.h>

#define CANDIDATES 6
#define FIELDS 5
#define MAX_SCORE 100

typedef struct {
    char name[50];
    char id[7];
    int scores[FIELDS];
    int totalScore;
} Candidate;

void initializeCandidates(Candidate candidates[]);
void inputScores(Candidate candidates[], const char* judgeName, const char* expertise);
void displayScores(const Candidate candidates[]);
int findCandidateIndexById(const Candidate candidates[], const char* id);
void modifyScores(Candidate candidates[]);
void calculateTotalScores(Candidate candidates[]);
void displayFinalSelection(const Candidate candidates[]);

int main() {
    Candidate candidates[CANDIDATES];
    char judgeName[50];
    char expertise[20];
    char submitChoice;

    initializeCandidates(candidates);

    while (1) {
        printf("####################################\n");
        printf("#       오디션 심사 결과 입력       #\n");
        printf("####################################\n");

        printf("> 심사자 이름: ");
        scanf_s("%49s", judgeName, (unsigned)sizeof(judgeName));
        printf("> 전문 분야 (음악/댄스/보컬/비주얼/전달력): ");
        scanf_s("%19s", expertise, (unsigned)sizeof(expertise));

        inputScores(candidates, judgeName, expertise);

        printf("입력을 모두 완료했습니다.\n입력하신 내용을 검토하세요!\n");
        displayScores(candidates);

        printf("제출하시겠습니까? (Y/N): ");
        scanf_s(" %c", &submitChoice, 1);

        if (submitChoice == 'Y' || submitChoice == 'y') {
            printf("***최종 제출을 완료했습니다.***\n");
            break;
        }
        else if (submitChoice == 'N' || submitChoice == 'n') {
            modifyScores(candidates);
        }
    }

    calculateTotalScores(candidates);
    displayFinalSelection(candidates);

    return 0;
}

void initializeCandidates(Candidate candidates[]) {
    strcpy_s(candidates[0].name, sizeof(candidates[0].name), "박지연");
    strcpy_s(candidates[0].id, sizeof(candidates[0].id), "000001");

    strcpy_s(candidates[1].name, sizeof(candidates[1].name), "Ethan Smith");
    strcpy_s(candidates[1].id, sizeof(candidates[1].id), "000002");

    strcpy_s(candidates[2].name, sizeof(candidates[2].name), "Helena Silva");
    strcpy_s(candidates[2].id, sizeof(candidates[2].id), "000003");

    strcpy_s(candidates[3].name, sizeof(candidates[3].name), "Liam Wilson");
    strcpy_s(candidates[3].id, sizeof(candidates[3].id), "000004");

    strcpy_s(candidates[4].name, sizeof(candidates[4].name), "Sophia Kim");
    strcpy_s(candidates[4].id, sizeof(candidates[4].id), "000005");

    strcpy_s(candidates[5].name, sizeof(candidates[5].name), "Daniel Chen");
    strcpy_s(candidates[5].id, sizeof(candidates[5].id), "000006");

    for (int i = 0; i < CANDIDATES; i++) {
        for (int j = 0; j < FIELDS; j++) {
            candidates[i].scores[j] = 0;
        }
        candidates[i].totalScore = 0;
    }
}

void inputScores(Candidate candidates[], const char* judgeName, const char* expertise) {
    int fieldIndex;
    if (strcmp(expertise, "음악") == 0) fieldIndex = 0;
    else if (strcmp(expertise, "댄스") == 0) fieldIndex = 1;
    else if (strcmp(expertise, "보컬") == 0) fieldIndex = 2;
    else if (strcmp(expertise, "비주얼") == 0) fieldIndex = 3;
    else if (strcmp(expertise, "전달력") == 0) fieldIndex = 4;
    else {
        printf("잘못된 분야입니다.\n");
        return;
    }

    for (int i = 0; i < CANDIDATES; i++) {
        int score;
        do {
            printf("후보자: %s\n%s: ", candidates[i].name, expertise);
            scanf_s("%d", &score);
            if (score < 10 || score > MAX_SCORE) {
                printf("잘못된 값입니다. 10에서 100 사이의 점수를 입력하세요.\n");
            }
        } while (score < 10 || score > MAX_SCORE);
        candidates[i].scores[fieldIndex] = score;
    }
}

void displayScores(const Candidate candidates[]) {
    printf("------------------------------------\n");
    for (int i = 0; i < CANDIDATES; i++) {
        printf("%s: ", candidates[i].name);
        for (int j = 0; j < FIELDS; j++) {
            printf("%d ", candidates[i].scores[j]);
        }
        printf("\n");
    }
    printf("------------------------------------\n");
}

int findCandidateIndexById(const Candidate candidates[], const char* id) {
    for (int i = 0; i < CANDIDATES; i++) {
        if (strcmp(candidates[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void modifyScores(Candidate candidates[]) {
    char id[7];
    int fieldIndex, newScore;

    while (1) {
        printf("수정할 후보자의 ID를 입력하세요 (종료하려면 'exit' 입력): ");
        scanf_s("%6s", id, (unsigned)sizeof(id));
        if (strcmp(id, "exit") == 0) break;

        int candidateIndex = findCandidateIndexById(candidates, id);
        if (candidateIndex == -1) {
            printf("잘못된 후보자 ID입니다.\n");
            continue;
        }

        printf("수정할 분야 (0:음악, 1:댄스, 2:보컬, 3:비주얼, 4:전달력): ");
        scanf_s("%d", &fieldIndex);

        do {
            printf("새 점수 (10~100): ");
            scanf_s("%d", &newScore);
            if (newScore < 10 || newScore > MAX_SCORE) {
                printf("잘못된 값입니다. 10에서 100 사이의 점수를 입력하세요.\n");
            }
        } while (newScore < 10 || newScore > MAX_SCORE);

        candidates[candidateIndex].scores[fieldIndex] = newScore;
    }
}

void calculateTotalScores(Candidate candidates[]) {
    for (int i = 0; i < CANDIDATES; i++) {
        candidates[i].totalScore = 0;
        for (int j = 0; j < FIELDS; j++) {
            candidates[i].totalScore += candidates[i].scores[j];
        }
    }
}

void displayFinalSelection(const Candidate candidates[]) {
    printf("=======================================\n");
    printf("후보 선발 결과 집계 중 ...\n");
    printf("=======================================\n");

    // 총점 내림차순 정렬
    Candidate sortedCandidates[CANDIDATES];
    memcpy(sortedCandidates, candidates, sizeof(sortedCandidates));  // candidates 배열 복사

    for (int i = 0; i < CANDIDATES - 1; i++) {
        for (int j = i + 1; j < CANDIDATES; j++) {
            if (sortedCandidates[i].totalScore < sortedCandidates[j].totalScore) {
                Candidate temp = sortedCandidates[i];
                sortedCandidates[i] = sortedCandidates[j];
                sortedCandidates[j] = temp;
            }
        }
    }

    printf("#######################################\n");
    printf("# 밀리웨이즈의 멤버가 된 걸 축하합니다!  #\n");
    printf("#######################################\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, sortedCandidates[i].name);
    }
}
