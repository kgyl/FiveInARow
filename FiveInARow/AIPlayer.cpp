#include "stdafx.h"
#include "AIPlayer.h"

int EvaluatePosition(CChessManager& manager, int x, int y, COLOR aiColor) {
    // 简化：只检查该位置周围是否有己方棋子，若有 +1 分
    int score = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            CChess* neighbor = manager.GetQz(x + dx, y + dy);
            if (neighbor && neighbor->GetColor() == aiColor)
                score++;
        }
    }
    return score;
}

CPoint AIPlayer::GetNextMove(CChessManager& manager) {
    int maxScore = -1;
    CPoint bestMove(-1, -1);

    for (int x = 0; x < MAX_COLS; x++) {
        for (int y = 0; y < MAX_ROWS; y++) {
            if (manager.GetQz(x, y) == nullptr) {
                int score = EvaluatePosition(manager, x, y, WHITE); // AI 设为白子
                if (score > maxScore) {
                    maxScore = score;
                    bestMove = CPoint(x, y);
                }
            }
        }
    }

    return bestMove;
}
