#include"DxLib.h"
#include"keyboard.h"

#define CENTER_X 320      //��  720�@�p�ō�����L�[�{�[�h�𖳗���蒆�S�Ɏ����Ă���
#define CENTER_Y 120      //����480�@�@�@�@�@�@�@�@�@�@�s�v�Ȏ��� CENTER_X,Y ��0�ɂ��Ă�������


#define ALPHA_MAX 26      //�A���t�@�x�b�g����

#define OUT_WIDTH 45 + CENTER_X     //��ʍ��[�`�L�[�{�[�h�܂ł̕�
#define OUT_HEIGHT 200 + CENTER_Y    //��ʏ�[�`�L�[�{�[�h�܂ł̍���
#define SPACE 10          //�L�[�Ԃ̃X�y�[�X
#define KEY_WIDTH 40      //�m�[�}���L�[�̕�

const int CurStdX = OUT_WIDTH + SPACE + 5;    //�J�[�\����X���W�    (�u5�v�̓J�[�\���̕� �j
const int CurStdY = OUT_HEIGHT + SPACE + 5;   //�J�[�\����Y���W� 

//���͕���   �i���ۂɕ\������Ă���L�[�{�[�h�Ɠ����z�u�j
const char AllStr[5][ALPHA_MAX / 2 + 1] = {
	"ABCDEFGHIJKLM",
	"NOPQRSTUVWXYZ",
	"abcdefghijklm",
	"nopqrstuvwxyz",
	"0123456789"
};


/************* �ϐ� *************/

int backimage = 0;            //�w�i�摜

int keyboardimage = 0;        //�L�[�{�[�h�摜

int Cursorimage[2] = { 0 };   //�m�[�}���J�[�\���摜  0 : �ʏ펞�@�@1 : �����ꂽ�Ƃ�
int Cancelimage[2] = { 0 };   //  �u�~�v�J�[�\���摜
int OKimage[2] = { 0 };       //  �uOK�v�J�[�\���摜
///////////////////////////////////////////////////////////////////////////////////////

bool pushFlag = false;           //A���@������Ă���/������ĂȂ� �t���O    TRUE:������Ă���@FALSE:������Ă��Ȃ�

int frame = 0;                   //�t���[�����J�E���g

//�ړ���   (�L�[�{�[�h�Z�Ԗ�)
int movekeyX = 0;
int movekeyY = 0;

CURSOR_TYPE CURSOR_NOW = CURSOR_TYPE::NORMAL;  //���݂̃J�[�\��

char InputName[11];              //���͂�������������z�� 0�`9�ɕ���(10�������)�@10�Ԗڂɂ� \0 �ł�
int input_Pos;                   //���͒��̔z��́Z�Ԗ�

/********************************/



//��������
void KeyBoardInit()
{
	//�J�[�\���̏����ʒu��"A"
	movekeyX = 0;             //������0�Ԗ�
	movekeyY = 0;             //������1�Ԗ�

	//�J�[�\���̏����ʒu�́uA�v�Ȃ̂Ńm�[�}��
	CURSOR_NOW = CURSOR_TYPE::NORMAL;

	//���͕�����@������
	for (int i = 0; i < 10; i++)
	{
		InputName[i] = 0;
	}
	InputName[10] = '\0';     //�z��̈�ԍŌ��"\0"(�I�[�̖ڈ�)�����Ă���

	input_Pos = -1;           //

	pushFlag = FALSE;         //�ŏ���A�{�^���͉�����Ă��Ȃ�
}

//�摜�ǂݍ���
int LoadKeyBoardImgaes()
{
	//�w�i
	if ((backimage = LoadGraph("images/inputname.png")) == -1) return -1;
	//�L�[�{�[�h
	if ((keyboardimage = LoadGraph("images/KeyBoard03.png")) == -1) return -1;

	//�����ǂݍ��݁@��������/�����ĂȂ� ���A�������摜

	//�m�[�}���J�[�\��
	if ((LoadDivGraph("images/Link_Normal1.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
	//�u�~�v�J�[�\��
	if ((LoadDivGraph("images/Link_Cancel1.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
	//�uOK�v�J�[�\��
	if ((LoadDivGraph("images/Link_Space1.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;

	return 0;
}

//�L�[�{�[�h�`��
void KeyBoard_Draw()
{
	//�w�i
	DrawGraph(0, 0, backimage, FALSE);
	//�L�[�{�[�h
	DrawGraph(45 + CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);


	// �m�[�}��(A�`Z,a�`z,0�`9)�E�u�~�v�E�u�n�j�v�ɂ���ĉ摜�ω��@ switch���ő���
	// �@�@�@�@�@�@�@�@�����E�����Ȃ��ɂ���ĉ摜�ω��@�@�@�@�@�@�@ �摜�z��� PushFlg �ő���

	//�摜�z��� 0�Ԗ� �́u�����Ă��Ȃ��v�J�[�\���@�@1�Ԗڂ� �u�����Ă���v�J�[�\��

	switch (CURSOR_NOW)
	{
	case CURSOR_TYPE::NORMAL:    //�m�[�}���J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[pushFlag], TRUE);
		break;

	case CURSOR_TYPE::CANCEL:    //�u�~�v�J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[pushFlag], TRUE);
		break;

	case CURSOR_TYPE::DONE:      //�uOK�v�J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[pushFlag], TRUE);
		break;

	default:
		break;
	}

	//���͒��̕�����\��
	DrawInputInfo();
}

//�X�V
void KeyBoard_Update(int nowkey)
{
	//�t���[�����J�E���g
	frame++;


	//�� �E 
	if (nowkey & PAD_INPUT_RIGHT)
	{
		if (CursorControl() == true)
		{
			movekeyX++;     //�^�C�~���O���� + �ړ�
		}
		if (movekeyX > 12) movekeyX = 0;   //�E�[�ȏ�ō��[��

		CURSOR_NOW = CURSOR_TYPE::NORMAL;  //���݂̃L�[�̓m�[�}��
	}

	//�� ��
	if (nowkey & PAD_INPUT_LEFT)
	{
		if (CursorControl() == true)
		{
			movekeyX--;     //�^�C�~���O���� + �ړ�
		}
		if (movekeyX < 0) movekeyX = 12;     //���[�ȏ�ŉE�[��

		CURSOR_NOW = CURSOR_TYPE::NORMAL;    //���݂̃L�[�̓m�[�}��
	}

	//�� ��
	if (nowkey & PAD_INPUT_UP)
	{

		if (CursorControl() == true)
		{
			movekeyY--;     //�^�C�~���O���� + �ړ�
		}
		if (movekeyY <= 0) movekeyY = 0;     //��[�ŃX�g�b�v

		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
	}

	//�� ��
	if (nowkey & PAD_INPUT_DOWN)
	{

		if (CursorControl() == true)
		{
			movekeyY++;     //�^�C�~���O���� + �ړ�
		}

		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
	}

	//�u�~�v�{�^��   �ua�`z�v�i��艺 ���� �u9�v�L�[���E��
	if (movekeyY == 4 && movekeyX >= 10)
	{
		movekeyX = 10;                       //�{�^���̈ʒu

		CURSOR_NOW = CURSOR_TYPE::CANCEL;         //���݂̃L�[�̓L�����Z���u�~�v
	}

	//�uOK�v�{�^��   �L�[�{�[�h�ŉ��i��艺
	if (movekeyY >= 5)
	{
		movekeyX = 4;                        //�{�^���̈ʒu
		movekeyY = 5;

		CURSOR_NOW = CURSOR_TYPE::DONE;           //���݂̃L�[��DONE�uOK�v
	}
}

//�J�[�\���̈ړ��E�{�^���̒������𒲐�
bool CursorControl()
{
	int timing = 8;
	if (frame % timing == 0) return true;
	//frame = 0;

	return false;
}

//B�{�^���������ꂽ���̏���
int KeyBoard_PushB(int nowkey, char* name)
{
	//�@A�{�^���������Ă����
	if (nowkey & PAD_INPUT_B)
	{
		//�������ł̘A�����͂̃^�C�~���O�𒲐��iPC�̂悤�ȁj
		if (CursorControl() == true)
		{
			// "A�`Z","a�`z","1�`9"�̏�ŉ����ꂽ
			if (CURSOR_NOW == CURSOR_TYPE::NORMAL)
			{
				pushFlag = true;        //������Ă����

				++input_Pos;            //���͈ʒu����E��

				//�����10����   �i�z���0�`9�j
				if (input_Pos > 9) input_Pos = 9;

				//�����z��ɓ���
				InputName[input_Pos] = AllStr[movekeyY][movekeyX];

			}
			else if (CURSOR_NOW == CURSOR_TYPE::CANCEL)                  //�u�~�v�L�[�̏�ŉ����ꂽ�@�ꕶ���폜
			{
				pushFlag = true;        //������Ă����

				//�ꕶ���ł����͂���Ă���Έꕶ������
				if (InputName[input_Pos] != 0) InputName[input_Pos] = 0; //0 �͉������͂���Ă��Ȃ����

				input_Pos--;            //���͈ʒu�������

				//���͈ʒu�͍Œ�-1�܂�
				if (input_Pos < -1) input_Pos = -1;
			}
			else if (CURSOR_NOW == CURSOR_TYPE::DONE)                  //�uOK�v�L�[�̏�ŉ����ꂽ�@�m��
			{
				//�ꕶ�������͂���Ă��Ȃ��ꍇ�͊m��ł��Ȃ�
				if (InputName[input_Pos] != 0)
				{
					//�ꕶ���ł����̓A��

					InputName[input_Pos + 1] = '\0';       //�Ō�̕����̈�E��'\0'

					//�����L���O�ɓ��͓��e���Z�b�g
					strcpy_s(name, 11, InputName);

					return 1;   //�I��
				}
				else
				{
					//�_������I�@�@�Ȍ��ʉ�
				}
			}
		}
	}

	else
	{
		pushFlag = false;          //������Ă��Ȃ���
	}

	return 0;
}


//���͏��\��
void DrawInputInfo()
{
	if (InputName[0] == 0)
	{
		//SetDrawBlendMode
		SetFontSize(20);
		DrawString(200 + CENTER_X, 125 + CENTER_Y, "�E �E ���O����� �E �E", 0xffffff);
	}

	for (int i = 0; InputName[i] != '\0'; i++)
	{
		SetFontSize(30);
		DrawFormatString((220 + 20 * i) + CENTER_X, 120 + CENTER_Y, 0xffffff, " %c", InputName[i]);
	}
}


//if (KeyBoard_PushA(key, g_Ranking[RANKING_DATA - 1].name) == 1)
//{
//	g_Ranking[RANKING_DATA - 1].score = score;   // �����L���O�f�[�^�ɃX�R�A��o�^
//	SortRanking();                               // �����L���O���בւ�
//	SaveRanking();                               // �����L���O�f�[�^�̕ۑ�
//	gamemode = 3;                                // �Q�[�����[�h�̕ύX
//}
//else
//{
//	KeyBoard_Draw();
//	KeyBoard_Update(key);
//}