#pragma once

namespace PW
{
	namespace Map
	{
		namespace WMAP
		{
			public ref struct Water
			{
				public: float CenterX;
				public: float CenterY;
				public: float SpanX;
				public: float SpanY;
				public: float Altitude;
			};

			public ref class WMAP
			{
				public: int Version;
				public: float MapWidth;
				public: float MapHeight;
				public: array<Water^>^ Surfaces;
				public: Image^ Overlay;

				public: void Load(String^ File)
				{
					FileStream^ fr = File::OpenRead(File);
					BinaryReader^ br = gcnew BinaryReader(fr);

					Version = br->ReadInt32();
					MapWidth = br->ReadSingle();
					MapHeight = br->ReadSingle();
					int surface_count = br->ReadInt32();

					Surfaces = gcnew array<PW::Map::WMAP::Water^>(surface_count);

					// flip lines vertical while loading
					for(int i=0; i<Surfaces->Length; i++)
					{
						Surfaces[i] = gcnew PW::Map::WMAP::Water();
						Surfaces[i]->CenterX = br->ReadSingle();
						Surfaces[i]->CenterY = br->ReadSingle();
						Surfaces[i]->SpanX = br->ReadSingle();
						Surfaces[i]->SpanY = br->ReadSingle();
						Surfaces[i]->Altitude = br->ReadSingle();
					}

					br->Close();
					fr->Close();
				}
				public: void Save(String^ File)
				{
					FileStream^ fw = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
					BinaryWriter^ bw = gcnew BinaryWriter(fw);

					bw->Write(Version);
					bw->Write(MapWidth);
					bw->Write(MapHeight);
					bw->Write(Surfaces->Length);

					for(int i=0; i<Surfaces->Length; i++)
					{
						bw->Write(Surfaces[i]->CenterX);
						bw->Write(Surfaces[i]->CenterY);
						bw->Write(Surfaces[i]->SpanX);
						bw->Write(Surfaces[i]->SpanY);
						bw->Write(Surfaces[i]->Altitude);
					}

					bw->Close();
					fw->Close();
				}
			};
		}
	}
}