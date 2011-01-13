#pragma once

public ref struct Category
{
    array<unsigned char>^ name; // 128 Byte Unicode
    int sub_cats_count;
	array<array<unsigned char>^>^ sub_cats; // Array [max 8] of 128 Byte Unicode
};

public ref struct Item
{
    int shop_id;
    int cat_index;
    int sub_cat_index;

    array<unsigned char>^ surface_path; // 128 Byte GBK

    int item_id;
    int item_amount;

    int price1;
	int value1;
	int duration1;
	int price2;
	int value2;
	int duration2;
	int price3;
	int value3;
	int duration3;

    int unknown1; // 16 Byte
	int unknown2; // 16 Byte
	int unknown3; // 16 Byte
	int state; // 0->normal, 1->new, 2->hot, 4->gift
    array<unsigned char>^ description; // 1024 Byte Unicode
    array<unsigned char>^ name; // 64 Byte Unicode
};

public ref struct Boutique
{
    int timestamp;
    int item_count;
    array<Item^>^ items;
    array<Category^>^ categories; // [8]
};