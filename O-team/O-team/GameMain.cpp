#include"DxLib.h"
#include"GameMain.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"
#include"Player.h"


#define DRAWAREA_X 980 //�`��G���A�Œ�l

//�U���̃X�s�[�h  5 �` 10
#define SPEED_ATTACK (GetRand(4) + 1) + 5

//�h��̃X�s�[�h  5 �` 9
#define SPEED_ARMOR  (GetRand(3) + 1) + 5

//�h��ő�\����
#define ARMOR_MAX 25

//�U���ő�\����
#define ATTACK_MAX 15

//�������ԁ@�h��
#define ARMOR_LIMIT 600

//�������ԁ@�U��
#define ATTACK_LIMIT 1200

//�h��̔z��
Flying_object** obj_armor;     //���N���X�^�|�C���^

//�U���̔z��
Flying_object** obj_attack;

//�v���C���[
Player* player;

//�t���[�����J�E���g
int frameCount = 0;
int death_frame = 0;

//���݂̃^�[��
Turn now_turn;

int image_Back[2];     //�w�i�摜 1,2
int image_CorO[2];     //Clear or Over  �ł�
int image_R_area;      //�E�̕`��G���A�摜  
int image_hukidashi;   //�����o��
float now_hp = 0.0f;   //���݂�HP�i�E�G���A���̃Q�[�W�Ŏg�p�j
int font_handle;       //�t�H���g

//�T�E���h�p�ϐ�
int GameMainBGM;
int GetSE;

int SpearSE;
int IronSE;
int PoisonSE;


//�e�X�g�p
char Turn_str[][7] = { "Catch","Attack","END" };

//����ׂ�
char Talk_str[][10] = { " ","����","����","����" ,"��[��","�L�^","������","������"};
int talk_num = 0;    //����ׂ�ԍ�
int talk_frame = 0;

//�Q�[�����C���摜�ǂݍ���
int LoadGameMainImages()
{
	//�E�̕`��G���A�摜
	if ((image_R_area = LoadGraph("images/RightBox.png")) == -1) return -1;
	if ((image_hukidashi = LoadGraph("images/RightBox2.png")) == -1) return -1;

	//Clear or Over  �ł�
	LoadDivGraph("images/GameMain/Game_CorO.png", 2, 2, 1, 1280, 720, image_CorO);

	//�w�i
	LoadDivGraph("images/GameMain/BackLink.png", 2, 2, 1, 1280, 720, image_Back);

	return 0;
}

//�Q�[���T�E���h�Ǎ���
int LoadGameMainSounds() {
	if ((GameMainBGM = LoadSoundMem("sounds/bgm/GameMain.wav")) == -1) return -1;
	if ((GetSE = LoadSoundMem("sounds/se/Get.wav")) == -1) return -1;
	if ((SpearSE = LoadSoundMem("sounds/se/�|��.wav")) == -1) return -1;
	if ((IronSE = LoadSoundMem("sounds/se/�S��.wav")) == -1) return -1;
	if ((PoisonSE = LoadSoundMem("sounds/se/��.wav")) == -1) return -1;
}

//�Q�[�����C�����������i�R���X�g���N�^����j
void GameMain_Init() 
{
	LoadGameMainSounds();

	//防具10個分のメモリを確保
	obj_armor = new Flying_object * [ARMOR_MAX];

	//������
	for (int i = 0; i < ARMOR_MAX; i++) obj_armor[i] = nullptr;

	//�h��10���̃��������m��
	obj_attack = new Flying_object * [ATTACK_MAX];

	//������
	for (int i = 0; i < ATTACK_MAX; i++) obj_attack[i] = nullptr;

	//�v���[���[�̃��������m�ہE�R���X�g���N�^�Ăяo��
	player = new Player();

	//�ŏ��̃^�[���͑���
	now_turn = Turn::CATCH;

	frameCount = 0;
	death_frame = 0;

	now_hp = 0.0f;
	talk_num = 0;
	talk_frame = 0;

	//�摜
	player->LoadImages();

	//�Q�[�����C�����Ŏg���t�H���g���쐬      NULL �̂Ƃ����Windows�W�������̃t�H���g���g�������i?�j
	font_handle = CreateFontToHandle(NULL, 30, 10, DX_FONTTYPE_ANTIALIASING_8X8);
}

//�Q�[�����C���I�������i�f�X�g���N�^�̑���j
void GameMain_Final() {
	delete obj_armor;
	delete obj_attack;
	delete player;

	//�t�H���g���폜
	DeleteFontToHandle(font_handle);
}

//�h��  �����E�X�V�E�폜
void Armor_Update(){
	int armor_count;   //�h��z��́Z�Ԗڂ����Ă��邩

	//�z�������݂�
	for (armor_count = 0; armor_count < ARMOR_MAX; armor_count++)
	{
		//nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
		if (obj_armor[armor_count] == nullptr) break;

		//�X�V�@�i�ړ��j
		obj_armor[armor_count]->Update();
		if (player->Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])))
		{
			//DrawString(0, 20, "Hit", 0xffffff);

			//HP��������
			player->SetHP(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])->GetHP());

			//ChangeNextPlayVolumeSoundMem(   , RankUpSE);  //次に流す音量を調整  ～２５５  255が通常
			PlaySoundMem(GetSE, DX_PLAYTYPE_BACK);

			//しゃべる
			talk_num = 5;
		}

		//��ʊO�ɓ��B,�܂��̓v���C���[��Hit�ō폜
		if (obj_armor[armor_count]->CheckScreenOut() == true
			|| player->Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])) == true)
		{
			delete obj_armor[armor_count];         //���B�������폜
			obj_armor[armor_count] = nullptr;      //�폜�����z��̗v�f��������

			//�z����l�߂�
			for (int i = armor_count; i < (ARMOR_MAX - 1); i++)
			{
				//���̗v�f�� nullptr �Ȃ�l�߂�K�v���Ȃ��̂Ŕ�����
				if (obj_armor[i + 1] == nullptr) break;

				obj_armor[i] = obj_armor[i + 1];   //�l�߂�
				obj_armor[i + 1] = nullptr;        //�l�߂�ꂽ�v�f�͏�����
			}
			armor_count--;
		}
	}

	//�z��ɋ�v�f������΃I�u�W�F�N�g�𐶐�����
	if (armor_count < ARMOR_MAX && obj_armor[armor_count] == nullptr)
	{
		//�^�C�v
		int r_type = GetRand(2);       //�O�`�Q�̗���

		//�ϋv�l
		int r_dura = 100;   // �Ƃ肠����

		//�����W�i�����j�@�@�����W�� 1300�Œ�i��ʊO�E���j
		int r_y = (GetRand(10) * 60) + 60;

		//�X�s�[�h�i��� 5�ȏ�j
		int r_speed = SPEED_ARMOR;//(GetRand(3) + 1) + 5;

		//��������@�@�@�@�@�@�@                  �ϋv�l   ���@�@���@ ��߰��
		obj_armor[armor_count] = new Flying_Armor(static_cast<Armor_Type>(r_type), r_dura, 1300, r_y, r_speed);
	}
}

//�U��  �����E�X�V�E�폜
void Attack_Update() {
	int attack_count;   //�h��z��́Z�Ԗڂ����Ă��邩

	//�z�������݂�
	for (attack_count = 0; attack_count < ATTACK_MAX; attack_count++)
	{
		//nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
		if (obj_attack[attack_count] == nullptr) break;

		//�X�V�@�i�ړ��j
		obj_attack[attack_count]->Update();
		if (player->Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])))
		{
			//�_���[�W��H�炤
			player->SetHP((dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetAttackDamage(player->GetHP())) * -1);
			switch (dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetType())
			{
			case Attack_Type::SPEAR:
				PlaySoundMem(SpearSE, DX_PLAYTYPE_BACK);
				talk_num = 1;
				break;

			case Attack_Type::IRON:
				PlaySoundMem(IronSE, DX_PLAYTYPE_BACK);
				talk_num = 2;
				break;

			case Attack_Type::POISON:
				ChangeNextPlayVolumeSoundMem(200, PoisonSE);  //次に流す音量を調整  ～２５５  255が通常
				PlaySoundMem(PoisonSE, DX_PLAYTYPE_BACK);
				talk_num = 3;
				break;

			default:
				break;
			}
		}

		//��ʊO�ɓ��B�A�܂��̓v���C���[��Hit�ō폜
		if (obj_attack[attack_count]->CheckScreenOut() == true
			|| player->Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])) == true)
		{
			delete obj_attack[attack_count];         //���B�������폜
			obj_attack[attack_count] = nullptr;      //�폜�����z��̗v�f��������

			//�z����l�߂�
			for (int i = attack_count; i < (ATTACK_MAX - 1); i++)
			{
				//���̗v�f�� nullptr �Ȃ�l�߂�K�v���Ȃ��̂Ŕ�����
				if (obj_attack[i + 1] == nullptr) break;

				obj_attack[i] = obj_attack[i + 1];   //�l�߂�
				obj_attack[i + 1] = nullptr;        //�l�߂�ꂽ�v�f�͏�����
			}
			attack_count--;
		}
	}

	//�z��ɋ�v�f������΃I�u�W�F�N�g�𐶐�����
	if (attack_count < ATTACK_MAX && obj_attack[attack_count] == nullptr)
	{
		//�^�C�v
		int r_type = GetRand(2);       //�O�`�Q�̗���

		//�����W�i�����j�@�@�����W�� 1300�Œ�i��ʊO�E���j
		int r_y = (GetRand(10) * 60) + 60;

		//�X�s�[�h�i��� 5�ȏ�j
		int r_speed = SPEED_ATTACK; //(GetRand(3) + 1) + 5;

		//��������@�@�@�@�@�@�@                  �^�C�v   ���@�@���@ ��߰��
		obj_attack[attack_count] = new Flying_Attack((r_type), 1300, r_y, r_speed);
	}
}

//�Q�[�����C���X�V�E�v�Z
void GameMain_Update()
{
	ChangeNextPlayVolumeSoundMem(180, GameMainBGM);  //次に流す音量を調整  ～２５５  255が通常
	PlaySoundMem(GameMainBGM, DX_PLAYTYPE_LOOP, FALSE);

	//右エリア内ゲージ用
	now_hp = static_cast<float>(player->GetHP() * 0.5);
	if (now_hp < 0.0f) now_hp = 0.0f;  //0��艺����Ȃ�

	//����ׂ�
	talk_frame++;
	if (talk_frame % 120 == 0 && now_turn != Turn::END)
	{
		talk_num = 0;
		talk_frame = 0;
	}


	switch (now_turn)
	{
	case Turn::CATCH:

		player->Update();
		Armor_Update();
		break;

	case Turn::ATTACK:

		player->Update();

		//�^�[���؂�ւ���E2�b�҂�
		if (frameCount > 120) Attack_Update();
		else
		{
			DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  //�Ó]
			talk_num = 7;
		}
		break;

	case Turn::END:

		death_frame++;
		//�v���C���[��HP��0�ȏ�
		if (player->GetHP() > 0)
		{
			player->Update_Win();
			talk_num = 4;
		}
		else talk_num = 6;

		break;

	default:
		StopSoundMem(GameMainBGM);
		break;
	}
}

//�Q�[�����C���`��
void GameMain_Draw()
{

	switch (now_turn)
	{
	case Turn::CATCH:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawGraph(0, 0, image_Back[0], TRUE);     //�w�i
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		player->Draw();                           //�v���C���[�`��

		//�h��̕`��
		for (int i = 0; i < ARMOR_MAX; i++)
		{
			if (obj_armor[i] == nullptr) break;   //nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
			obj_armor[i]->Draw();                 //�v�f�����鎞�͕`��

		}

		break;

	case Turn::ATTACK:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(0, 0, image_Back[1], TRUE);     //�w�i
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (frameCount > 120) {}
		else DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  //�Ó]

		player->Draw();                           //�v���C���[�`��

		//�U���̕`��
		for (int i = 0; i < ATTACK_MAX; i++)
		{
			if (obj_attack[i] == nullptr) break;  //nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
			obj_attack[i]->Draw();                //�v�f������Ƃ��͕`��
		}
		break;

	case Turn::END:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(0, 0, image_Back[1], TRUE);     //�w�i
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		//�v���C���[��HP��0�ȏ�
		if (player->GetHP() > 0)
		{
			DrawGraph(0, 0, image_CorO[0], TRUE);    //Game Over
			player->Draw_Win();       //�v���C���[��`��
		}
		else
		{
			DrawGraph(0, 0, image_CorO[1], TRUE);    //Game Over
			player->Draw_Death();
		}
		break;

	default:
		break;
	}
}

//�Q�[�����C���`��G���A
void GameMain_DrawArea() {
	////�`��G���A
	//DrawBox(DRAWAREA_X, 0, 1280, 720, 0x00ddbb, TRUE);

	//SetFontSize(20);
	////Test
	//DrawFormatString(1130, 100, 0x000000, "Now : %s", Turn_str[static_cast<int>(now_turn)]);
	//DrawFormatString(1130, 130, 0x000000, "Time : %d", (frameCount / 60));

	DrawBox(1150, 80, 1250, 700, 0x1f1006, TRUE);                            //�Q�[�W�̌��

	//(float�^���g����DrawBox�炵���ł�)  �Q�[�W
	DrawBoxAA(1150.0f, (690.0f - now_hp), 1250.0f, 690.0f, 0xff0000, TRUE);  
	DrawGraph(0, 0, image_R_area, TRUE);                                     //�E�G���A�摜

	DrawFormatStringToHandle(1130, 20, 0xffffff, font_handle, "HP : %d", player->GetHP());

	//�v���C���[
	player->Draw_Right(1060, 620);
	if (talk_num != 0) DrawGraph(0, 0, image_hukidashi, TRUE);
	DrawFormatStringToHandle(1010, 412, 0x000000, font_handle, Talk_str[talk_num]);  //����ׂ�

	//����
	if (now_turn == Turn::CATCH)
	{
		DrawFormatStringToHandle(1000, 120, 0xffffff, font_handle, "Time : %d", (ARMOR_LIMIT/60) - (frameCount / 60));
	}
	else if (now_turn == Turn::ATTACK)
	{
		DrawFormatStringToHandle(1000, 120, 0xffffff, font_handle, "Time : %d", (ATTACK_LIMIT/60) - (frameCount / 60));
	}
	else{}
}

//�Q�[�����C�� �����L���O5�Ԗڂ̃X�R�A�E�X�R�A��ێ�����ϐ������炤
void GameMain(int &gamemode,int lowscore, int& g_score)
{
	GameMain_Update();    //�Q�[�����C���X�V�E�v�Z

	GameMain_Draw();      //�Q�[�����C���`��

	GameMain_DrawArea();  //�Q�[�����C���`��G���A

	//�t���[�������Z
	frameCount++;

	//if (now_turn == Turn::END && frameCount % 300 == 0)
	//{
	//	DrawString(100, 100, "end", 0xffffff);
	//}

	//Attack�^�[��30�b�@�܂��́@player��HP��0�ȉ��Ń^�[���؂�ւ��@�U���@���@�G���h
	if (now_turn == Turn::ATTACK && frameCount % ATTACK_LIMIT == 0 || player->GetHP() <= 0)
	{
		//�����L���O

		//if (player->GetHP() < 0)
		//{
		//	
		//}
		player->SetWin_PointY();  //Y���W��ێ�
		now_turn = Turn::END;     //���S��
		death_frame = frameCount;
	}

	//20�b�Ń^�[����؂�ւ�  �����@���@�U��
	if (now_turn == Turn::CATCH && frameCount % ARMOR_LIMIT == 0)
	{
		now_turn = Turn::ATTACK;  //�U�����󂯂�^�[��
		frameCount = 0;           //�J�E���g�����Z�b�g
	}

	//���S�܂���30�o�߂���7�b�o��
	if (now_turn == Turn::END && death_frame % 480 == 0)
	{
		g_score = player->GetHP();

		//ランキング最低スコアと比較
		if (g_score > lowscore)
		{
			StopSoundMem(GameMainBGM);
			gamemode = 5;  //ランキング入力へ
			GameMain_Final();
		}
		else
		{
			StopSoundMem(GameMainBGM);
			gamemode = 6; //リザルトへ
			GameMain_Final();
		}
	}
}