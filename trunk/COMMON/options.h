#pragma once

public ref struct Options
{
	String^ fileIn;
	String^ fileOut;

	bool gfxDowngrade;
	bool gfx152to150;
	bool gfx210to160;

	bool ecmDowngrade;
	bool ecmSoulsphereHook;
	double ecmSoulsphereHookTX;
	double ecmSoulsphereHookTY;
	double ecmSoulsphereHookTZ;

	bool sgcDowngrade;
};