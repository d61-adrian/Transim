//*********************************************************
//	Get_Pocket_Data.cpp - read the pocket lane file
//*********************************************************

#include "SubareaNet.hpp"

//---------------------------------------------------------
//	Get_Pocket_Data
//---------------------------------------------------------

bool SubareaNet::Get_Pocket_Data (Pocket_File &file, Pocket_Data &data)
{
	//---- do standard processing ----

	if (Data_Service::Get_Pocket_Data (file, data)) {

		//---- check the subarea boundary ----

		Dir_Data *dir_ptr = &dir_array [data.Dir_Index ()];
		Link_Data *link_ptr = &link_array [dir_ptr->Link ()];

		if (link_ptr->Type () == 0)  return (false);

		//---- copy the fields to the subarea file ----

		Db_Header *new_file = System_File_Header (NEW_POCKET);

		new_file->Copy_Fields (file);

		if (!new_file->Write ()) {
			Error (String ("Writing %s") % new_file->File_Type ());
		}
		npocket++;
	}
		
	//---- don't save the record ----

	return (false);
}
