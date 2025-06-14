#include "stdafx.h"
#include "AIPlayer.h"

int ScoreTable[6] = { 0, 10, 100, 1000, 10000, 1000000 }; // 1~5���÷�

int EvaluateDirection(CChessManager& manager, int x, int y, int dx, int dy, COLOR color) {
    int count = 0;
    for (int step = 1; step < 5; ++step) {
        int nx = x + dx * step;
        int ny = y + dy * step;
        CChess* c = manager.GetQz(nx, ny);
        if (c && c->GetColor() == color)
            count++;
        else
            break;
    }
    for (int step = 1; step < 5; ++step) {
        int nx = x - dx * step;
        int ny = y - dy * step;
        CChess* c = manager.GetQz(nx, ny);
        if (c && c->GetColor() == color)
            count++;
        else
            break;
    }
    return count >= 5 ? 5 : count;
}

int EvaluatePosition(CChessManager& manager, int x, int y, COLOR color) {
    if (manager.GetQz(x, y) != nullptr)
        return -1;

    // 4 ����������
    int score = 0;
    score += ScoreTable[EvaluateDirection(manager, x, y, 1, 0, color)];  // ����
    score += ScoreTable[EvaluateDirection(manager, x, y, 0, 1, color)];  // ����
    score += ScoreTable[EvaluateDirection(manager, x, y, 1, 1, color)];  // ���Խ���
    score += ScoreTable[EvaluateDirection(manager, x, y, 1, -1, color)]; // ���Խ���
    return score;
}

CPoint AIPlayer::GetNextMove(CChessManager& manager) {
    int maxScore = -1;
    CPoint bestMove(-1, -1);

    for (int x = 0; x < MAX_COLS; x++) {
        for (int y = 0; y < MAX_ROWS; y++) {
            // AI �Լ����ӵ÷�
            int aiScore = EvaluatePosition(manager, x, y, WHITE);
            // ��ֹ�����һ������
            int playerScore = EvaluatePosition(manager, x, y, BLACK);
            int score = max(aiScore, playerScore * 2); // ��ƫ���ڷ���

            if (score > maxScore) {
                maxScore = score;
                bestMove = CPoint(x, y);
            }
        }
    }

    return bestMove;
}
