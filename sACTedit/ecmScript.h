#pragma once

namespace PW
{
	namespace Models
	{
		public ref class ecmSCRIPT
		{
			public: ecmSCRIPT()
			{
			}
			protected: ~ecmSCRIPT()
			{
			}

			public: ArrayList^ Parameters;

			public: void SetAllParameters(array<String^>^ Properties)
			{
				Parameters = gcnew ArrayList(Properties);
			}

			public: void Fix(EcmFixOptions^ options)
			{
				// nothing to be done
				// decode base64 lines, fix them
			}

			public: array<String^>^ GetAllParameters()
			{
				array<String^>^ temp = gcnew array<String^>(Parameters->Count);

				for(int i=0; i<temp->Length; i++)
				{
					temp[i] = (String^)Parameters[i];
				}

				return temp;
			}
		};
	}
}