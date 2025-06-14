#pragma once
#include "UserInfo.h"
#include <vector>

class UserManager {
private:
    std::vector<UserInfo> m_users;
    CString m_dataPath = _T("users.dat");
public:
    bool Load();
    bool Save();
    bool RegisterUser(const CString& username, const CString& password);
    bool LoginUser(const CString& username, const CString& password, UserInfo& outUser);
    bool UpdateUser(const UserInfo& user);
    std::vector<UserInfo> GetAllUsers() const { return m_users; }
};
