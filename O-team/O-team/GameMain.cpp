#include"DxLib.h"
#include"GameMain.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"
#include"Player.h"

//�h��ő�\����
#define ARMOR_MAX 10 

//�U���ő�\����
#define ATTACK_MAX 10 

//�h��̔z��
Flying_object** obj_armor;     //���N���X�^�|�C���^

//�U���̔z��
Flying_object** obj_attack;

Player player;

//�t���[�����J�E���g
int frameCount = 0;

Turn now_turn;

//�e�X�g�p
char Turn_str[][7] = { "Catch","Attack" };

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

	//�ŏ��̃^�[���͑���
	now_turn = Turn::CATCH;
	frameCount = 0;
}

//�Q�[�����C���I�������i�f�X�g���N�^�̑���j
void GameMain_Final() {
	delete obj_armor;
	delete obj_attack;
	delete& player;
}

//�h��  �����E�X�V�E�폜
void Armor_Update()
{
	int armor_count;   //�h��z��́Z�Ԗڂ����Ă��邩

	//�z�������݂�
	for (armor_count = 0; armor_count < ARMOR_MAX; armor_count++)
	{
		//nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
		if (obj_armor[armor_count] == nullptr) break;

		//�X�V�@�i�ړ��j
		obj_armor[armor_count]->Update();
		if (player.Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])))
		{
			DrawString(0, 20, "Hit", 0xffffff);
			player.SetHP(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])->GetHP());
		}

		//��ʊO�ɓ��B,�܂��̓v���C���[��Hit�ō폜
		if (obj_armor[armor_count]->CheckScreenOut() == true
			|| player.Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])) == true)
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
		int r_dura = 30;   // �Ƃ肠����

		//�����W�i�����j�@�@�����W�� 1300�Œ�i��ʊO�E���j
		int r_y = (GetRand(10) * 60) + 60;

		//�X�s�[�h�i��� 5�ȏ�j
		int r_speed = (GetRand(3) + 1) + 5;

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
		if (player.Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])))
		{
			DrawString(0, 30, "Die", 0xff0000);
		}

		//��ʊO�ɓ��B�A�܂��̓v���C���[��Hit�ō폜
		if (obj_attack[attack_count]->CheckScreenOut() == true
			|| player.Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])) == true)
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
		int r_speed = (GetRand(3) + 1) + 15;

		//��������@�@�@�@�@�@�@                  �^�C�v   ���@�@���@ ��߰��
		obj_attack[attack_count] = new Flying_Attack((r_type), 1300, r_y, r_speed);
	}
}

//�Q�[�����C���X�V�E�v�Z
void GameMain_Update()
{
	player.Update();

	switch (now_turn)
	{
	case Turn::CATCH:

		Armor_Update();
		break;

	case Turn::ATTACK:

		//�^�[���؂�ւ���E2�b�҂�
		if (frameCount > 120) Attack_Update();
		break;
	default:
		break;
	}
}

//�Q�[�����C���`��
void GameMain_Draw()
{
	player.Draw();

	switch (now_turn)
	{
	case Turn::CATCH:

		//�h��̕`��
		for (int i = 0; i < ARMOR_MAX; i++)
		{
			if (obj_armor[i] == nullptr) break;   //nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
			obj_armor[i]->Draw();                 //�v�f�����鎞�͕`��
		}
		break;

	case Turn::ATTACK:

		//�U���̕`��
		for (int i = 0; i < ATTACK_MAX; i++)
		{
			if (obj_attack[i] == nullptr) break;  //nullptr����ɂ�nullptr�����Ȃ��̂Ń��[�v�𔲂���
			obj_attack[i]->Draw();                //�v�f������Ƃ��͕`��
		}
		break;
	default:
		break;
	}

	//Test
	DrawFormatString(0, 100, 0x000000, "Now : %s", Turn_str[static_cast<int>(now_turn)]);
	DrawFormatString(0, 130, 0x000000, "Time : %d", (frameCount / 60));
}

//�Q�[�����C��
void GameMain(int &gamemode)
{
	GameMain_Update();    //�Q�[�����C���X�V�E�v�Z

	GameMain_Draw();      //�Q�[�����C���`��

	//�t���[�������Z
	frameCount++;


	//Attack�^�[����30�b�ŏI��
	if (now_turn == Turn::ATTACK && frameCount % 1800 == 0)
	{
		//�����L���O

		gamemode = 6;   //���U���g��ʂ�
	}

	//20�b�Ń^�[����؂�ւ�
	if (now_turn == Turn::CATCH && frameCount % 600 == 0)
	{
		now_turn = Turn::ATTACK;  //�U�����󂯂�^�[��
		frameCount = 0;           //�J�E���g�����Z�b�g
	}

}