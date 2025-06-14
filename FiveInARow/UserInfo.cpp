#include "stdafx.h"
#include "UserInfo.h"

void UserInfo::Serialize(CArchive& ar) {
    if (ar.IsStoring()) {
        ar << username << password << wins << losses << totalTime;
    }
    else {
        ar >> username >> password >> wins >> losses >> totalTime;
    }
}