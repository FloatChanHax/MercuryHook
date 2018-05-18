#pragma once

class CPlayerVariables
{
public:
    void find();

    DWORD iWeaponID;
    DWORD bHasMeleeWeapon;
    DWORD bHasFlameThrower;

    DWORD bGlowEnabled;
    DWORD iTeam;
    DWORD iLifeState;
    DWORD iHealth;
    DWORD iClass;
    DWORD bReadyToBackstab;

    DWORD iWeaponSlot;
    DWORD iPlayerCond;
    DWORD iPlayerCondEx;
    DWORD iFlags;
    DWORD chName;

    DWORD vecViewOffset;
    DWORD vecVelocity;
    DWORD vecBaseVelocity;
    DWORD vecPunchAngle;

    DWORD f1flChargedDamage;
    DWORD nTickBase;
    DWORD f1flNextPrimaryAttack;

    DWORD hActiveWeapon;
    DWORD hOwner;

    DWORD iTeamDefinitionIndex;
};

class COffsets
{
public:
    DWORD dwWriteUserCmd;
    enum {

        ceateMoveOffset = 21,
        paintTraverseOffset = 41,
        keyEvent = 20,
        writeUserCmdToBuffferOffset = 23,
        processGetCvarValue = 28,
        processSetConVar = 3,
        getUsetCmdOffset = 8,
        runCommandOffset = 17,
        dispactchUserMessageOffset = 36,
        emitSound = 4,
        frameStageNotify = 35,

     };
};
