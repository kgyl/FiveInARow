#pragma once
class UserInfo
{
public:
    CString username;
    CString password;
    int wins = 0;
    int losses = 0;
    int totalTime = 0; // ����ʱ
    void Serialize(CArchive& ar);
};

