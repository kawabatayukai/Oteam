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
#define ARMOR_MAX 20

//�U���ő�\����
#define ATTACK_MAX 15

//�h��̔z��
Flying_object** obj_armor;     //���N���X�^�|�C���^

//�U���̔z��
Flying_object** obj_attack;

Player* player;

//�t���[�����J�E���g
int frameCount = 0;
int death_frame = 0;

Turn now_turn;

//�e�X�g�p
char Turn_str[][7] = { "Catch","Attack","END" };

//�Q�[�����C�����������i�R���X�g���N�^����j
void GameMain_Init() {
	//�h��10���̃��������m��
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

	//�摜
	player->LoadImages();
}

//�Q�[�����C���I�������i�f�X�g���N�^�̑���j
void GameMain_Final() {
	delete obj_armor;
	delete obj_attack;
	delete player;
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
			DrawString(0, 20, "Hit", 0xffffff);
			player->SetHP(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])->GetHP());
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
			DrawString(0, 30, "Die", 0xff0000);

			//�_���[�W��H�炤
			player->SetHP((dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetAttackDamage(player->GetHP())) * -1);
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
		else DrawBox(0, 0, 1280,720, 0x000000, TRUE);  //�Ó]

		break;

	case Turn::END:

		death_frame++;
		//�v���C���[��HP��0�ȏ�
		if (player->GetHP() > 0) player->Update_Win(); 

		break;

	default:
		break;
	}
}

//�Q�[�����C���`��
void GameMain_Draw()
{


	switch (now_turn)
	{
	case Turn::CATCH:

		player->Draw();

		//�h��̕`��
		for (int i = 0; i < ARMOR_MAX; i++)
		{
			if (obj_armor[i] == nullptr) break;   //nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
			obj_armor[i]->Draw();                 //�v�f�����鎞�͕`��

		}

		break;

	case Turn::ATTACK:

		player->Draw();

		//�U���̕`��
		for (int i = 0; i < ATTACK_MAX; i++)
		{
			if (obj_attack[i] == nullptr) break;  //nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
			obj_attack[i]->Draw();                //�v�f������Ƃ��͕`��
		}
		break;

	case Turn::END:

		//�v���C���[��HP��0�ȏ�
		if (player->GetHP() > 0) player->Draw_Win();       //�v���C���[��`��
		else player->Draw_Death();


		break;

	default:
		break;
	}
}

//�Q�[�����C���`��G���A
void GameMain_DrawArea() {
	//�`��G���A
	DrawBox(DRAWAREA_X, 0, 1280, 720, 0x00ddbb, TRUE);

	SetFontSize(20);
	//Test
	DrawFormatString(1130, 100, 0x000000, "Now : %s", Turn_str[static_cast<int>(now_turn)]);
	DrawFormatString(1130, 130, 0x000000, "Time : %d", (frameCount / 60));
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
	if (now_turn == Turn::ATTACK && frameCount % 1200 == 0 || player->GetHP() <= 0)
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
	if (now_turn == Turn::CATCH && frameCount % 600 == 0)
	{
		now_turn = Turn::ATTACK;  //�U�����󂯂�^�[��
		frameCount = 0;           //�J�E���g�����Z�b�g
	}

	//���S�܂���30�o�߂���7�b�o��
	if (now_turn == Turn::END && death_frame % 480 == 0)
	{
		g_score = player->GetHP();
		

		//�����L���O�Œ�X�R�A�Ɣ�r
		if (g_score > lowscore)
		{
			gamemode = 5;  //�����L���O���͂�
			GameMain_Final();
		}
		else
		{
			gamemode = 6; //���U���g��
			GameMain_Final();
		}
	}
}