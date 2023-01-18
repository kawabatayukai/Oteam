#pragma once

//�L�[�̎��
enum class CURSOR_TYPE
{
	NONE = 0,   // ����0�i�Ȃɂ�������Ă��Ȃ��j
	NORMAL,     // A�`B,a�`b,1�`9
	CANCEL,     //�u�~�v(�ЂƂ���)
	DONE,       //�uOK�v(�m��)

	MISS = 99
};


//��������
void KeyBoardInit();

//�摜�ǂݍ���
int LoadKeyBoardImgaes();

//���ʉ��ǂݍ���
int LoadSounds();

//�`��
void KeyBoard_Draw();

//�X�V
void KeyBoard_Update(int nowkey);                                 //nowkey�@��"������Ă���"�L�[
                                                                  //keyflg�@ ��"�����ꂽ�u��"�L�[
//�J�[�\���̈ړ��E�{�^���̒������𒲐�
bool CursorControl();

//B�{�^���������ꂽ���̏���  ���͂��I���� 1 ���Ԃ��Ă���
int KeyBoard_PushB(int nowkey, char* name);

//���͏��\��
void DrawInputInfo();