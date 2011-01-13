#pragma once

namespace PW
{
	namespace Models
	{
		public ref class ecmSKIN
		{
			public: ecmSKIN()
			{
			}
			protected: ~ecmSKIN()
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