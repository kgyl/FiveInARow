#include "stdafx.h"
#include "AIPlayer.h"

int ScoreTable[6] = { 0, 10, 100, 1000, 10000, 1000000 }; // 1~5连得分

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

    // 4 个方向评估
    int score = 0;
    score += ScoreTable[EvaluateDirection(manager, x, y, 1, 0, color)];  // 横向
    score += ScoreTable[EvaluateDirection(manager, x, y, 0, 1, color)];  // 纵向
    score += ScoreTable[EvaluateDirection(manager, x, y, 1, 1, color)];  // 主对角线
    score += ScoreTable[EvaluateDirection(manager, x, y, 1, -1, color)]; // 副对角线
    return score;
}

CPoint AIPlayer::GetNextMove(CChessManager& manager) {
    int maxScore = -1;
    CPoint bestMove(-1, -1);

    for (int x = 0; x < MAX_COLS; x++) {
        for (int y = 0; y < MAX_ROWS; y++) {
            // AI 自己落子得分
            int aiScore = EvaluatePosition(manager, x, y, WHITE);
            // 防止玩家下一步五连
            int playerScore = EvaluatePosition(manager, x, y, BLACK);
            int score = max(aiScore, playerScore * 2); // 更偏向于防守

            if (score > maxScore) {
                maxScore = score;
                bestMove = CPoint(x, y);
            }
        }
    }

    return bestMove;
}
