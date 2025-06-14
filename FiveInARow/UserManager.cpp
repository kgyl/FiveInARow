#include "stdafx.h"
#include "UserManager.h"
#include <afxcoll.h>
#include <fstream>

bool UserManager::Load() {
    CFile file;
    if (!file.Open(m_dataPath, CFile::modeRead | CFile::shareDenyNone))
        return false;

    CArchive ar(&file, CArchive::load);
    int count = 0;
    ar >> count;
    m_users.clear();
    for (int i = 0; i < count; ++i) {
        UserInfo user;
        user.Serialize(ar);
        m_users.push_back(user);
    }
    ar.Close();
    file.Close();
    return true;
}

bool UserManager::Save() {
    CFile file(m_dataPath, CFile::modeCreate | CFile::modeWrite);
    CArchive ar(&file, CArchive::store);
    ar << (int)m_users.size();
    for (auto& u : m_users)
        u.Serialize(ar);
    ar.Close();
    file.Close();
    return true;
}

bool UserManager::RegisterUser(const CString& username, const CString& password) {
    for (auto& u : m_users) {
        if (u.username == username) return false;
    }
    UserInfo user{ username, password };
    m_users.push_back(user);
    return Save();
}

bool UserManager::LoginUser(const CString& username, const CString& password, UserInfo& outUser) {
    for (auto& u : m_users) {
        if (u.username == username && u.password == password) {
            outUser = u;
            return true;
        }
    }
    return false;
}

bool UserManager::UpdateUser(const UserInfo& user) {
    for (auto& u : m_users) {
        if (u.username == user.username) {
            u = user;
            return true;
        }
    }
    return false;
}
