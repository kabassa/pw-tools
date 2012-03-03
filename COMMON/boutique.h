#pragma once

public ref struct Category
{
    array<unsigned char>^ name; // 128 Byte Unicode
    int sub_cats_count;
	array<array<unsigned char>^>^ sub_cats; // Array [max 8] of 128 Byte Unicode
};

public ref struct SaleOption
{
	unsigned int price;
	unsigned int expire_date;
	unsigned int duration;
	unsigned int start_date;
	int control_type;
	unsigned int day;
	unsigned int status;
	unsigned int flags;
};

public ref struct Item
{
	// for internal DB usage
	// if true the item will be exported to server file
	bool activate;

    int shop_id;
    int cat_index;
    int sub_cat_index;

    array<unsigned char>^ surface_path; // 128 Byte GBK

    int item_id;
    int item_amount;

	array<SaleOption^>^ sale_options; // length = 4

    array<unsigned char>^ description; // 1024 Byte Unicode
    array<unsigned char>^ name; // 64 Byte Unicode

	int gift_id;
	int gift_amount;
	int gift_duration;
	int log_price;
};

public ref struct Boutique
{
    int timestamp;
    int item_count;
    array<Item^>^ items;
    array<Category^>^ categories; // [8]
};

/*
type = class _GSHOP_ITEM
{
	public: int local_id;
	int main_type;
	int sub_type;
	unsigned int id;
	unsigned int num;
	class
	{
		public: unsigned int price;
		unsigned int end_time;
		unsigned int time;
		unsigned int start_time;
		int type;
		unsigned int day;
		unsigned int status;
		unsigned int flag;
	}
	buy[4];
	unsigned int idGift;
	unsigned int iGiftNum;
	unsigned int iGiftTime;
	unsigned int iLogPrice;
} 
*/