#pragma once

namespace PW
{
	namespace Data
	{
		namespace Gshop
		{
			public ref struct Category
			{
				array<unsigned char>^ Name; // 128 Byte Unicode
				array<array<unsigned char>^>^ SubCategories; // Array [max 8] of 128 Byte Unicode
			};

			public ref struct Item
			{
				int ShopID;
				int CategoryIndex;
				int SubCategoryIndex;

				array<unsigned char>^ SurfacePath; // 128 Byte GBK

				int ItemID;
				int ItemAmount;

				int Option1_Price;
				int Option1_Value;
				int Option1_Duration;
				int Option2_Price;
				int Option2_Value;
				int Option2_Duration;
				int Option3_Price;
				int Option3_Value;
				int Option3_Duration;

				int unknown1; // 16 Byte
				int unknown2; // 16 Byte
				int unknown3; // 16 Byte
				int State; // 0->normal, 1->new, 2->hot, 4->gift
				array<unsigned char>^ Description; // 1024 Byte Unicode
				array<unsigned char>^ Name; // 64 Byte Unicode
			};

			public ref class Boutique
			{
				public: Boutique(void)
				{
				}

				protected: ~Boutique()
				{
				}

				public: int Timestamp;
				public: array<Item^>^ Items;
				public: array<Category^>^ Categories; // [8]

				public: void Load(String^ File)
				{
					FileStream^ fr = File::OpenRead(File);
					BinaryReader^ br = gcnew BinaryReader(fr);

					Timestamp = br->ReadInt32();
					int item_count = br->ReadInt32();
					Items = gcnew array<Item^>(item_count);
					for(int i=0; i<Items->Length; i++)
					{
						Items[i] = gcnew Item();
						Items[i]->ShopID = br->ReadInt32();
						Items[i]->ShopID = i;
						Items[i]->CategoryIndex = br->ReadInt32();
						Items[i]->SubCategoryIndex = br->ReadInt32();
						Items[i]->SurfacePath = br->ReadBytes(128);
						Items[i]->ItemID = br->ReadInt32();
						Items[i]->ItemAmount = br->ReadInt32();
						Items[i]->Option1_Price = br->ReadInt32();
						Items[i]->Option1_Value = br->ReadInt32();
						Items[i]->Option1_Duration = br->ReadInt32();
						Items[i]->Option2_Price = br->ReadInt32();
						Items[i]->Option2_Value = br->ReadInt32();
						Items[i]->Option2_Duration = br->ReadInt32();
						Items[i]->Option3_Price = br->ReadInt32();
						Items[i]->Option3_Value = br->ReadInt32();
						Items[i]->Option3_Duration = br->ReadInt32();
						Items[i]->unknown1 = br->ReadInt32();
						Items[i]->unknown2 = br->ReadInt32();
						Items[i]->unknown3 = br->ReadInt32();
						Items[i]->State = br->ReadInt32();
						Items[i]->Description = br->ReadBytes(1024);
						Items[i]->Name = br->ReadBytes(64);
					}

					Categories = gcnew array<Category^>(8);
					for(int i=0; i<Categories->Length; i++)
					{
						Categories[i] = gcnew Category();
						Categories[i]->Name = br->ReadBytes(128);
						int sub_cats_count = br->ReadInt32();
						Categories[i]->SubCategories = gcnew array<array<unsigned char>^>(sub_cats_count);
						for(int n=0; n<Categories[i]->SubCategories->Length; n++)
						{
							Categories[i]->SubCategories[n] = br->ReadBytes(128);
						}
					}

					br->Close();
					fr->Close();
				}
				public: void Save(String^ File)
				{
					FileStream^ fw = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
					BinaryWriter^ bw = gcnew BinaryWriter(fw);

					bw->Write(Timestamp);
					bw->Write(Items->Length);
					int	shop_id = 0;
					for(int i=0; i<Items->Length; i++)
					{
						if(Items[i]->CategoryIndex>-1 && Items[i]->SubCategoryIndex>-1)
						{
							bw->Write(shop_id);
							bw->Write(Items[i]->CategoryIndex);
							bw->Write(Items[i]->SubCategoryIndex);
							bw->Write(Items[i]->SurfacePath);
							bw->Write(Items[i]->ItemID);
							bw->Write(Items[i]->ItemAmount);
							bw->Write(Items[i]->Option1_Price);
							bw->Write(Items[i]->Option1_Value);
							bw->Write(Items[i]->Option1_Duration);
							bw->Write(Items[i]->Option2_Price);
							bw->Write(Items[i]->Option2_Value);
							bw->Write(Items[i]->Option2_Duration);
							bw->Write(Items[i]->Option3_Price);
							bw->Write(Items[i]->Option3_Value);
							bw->Write(Items[i]->Option3_Duration);
							bw->Write(Items[i]->unknown1);
							bw->Write(Items[i]->unknown2);
							bw->Write(Items[i]->unknown3);
							bw->Write(Items[i]->State);
							bw->Write(Items[i]->Description);
							bw->Write(Items[i]->Name);

							shop_id++;
						}
					}
					/*
					if(shop_id != item_count)
					{
						MessageBox::Show("shop_id_count != item_count");
					}
					*/
					for(int i=0;i<8; i++)
					{
						bw->Write(Categories[i]->Name);
						bw->Write(Categories[i]->SubCategories->Length);
						/*
						if(Categories[i]->sub_cats->Length != Categories[i]->sub_cats_count)
						{
							MessageBox::Show("sub_cat_count != sub_cats->Length");
						}
						*/
						for(int n=0; n<Categories[i]->SubCategories->Length; n++)
						{
							bw->Write(Categories[i]->SubCategories[n]);
						}
					}

					bw->Close();
					fw->Close();
				}
			};
		}
	}
}