/* Copyright (C) 2009 Curtis Gedak
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* READ THIS!
 * This class was created in an effort to reduce the complexity of the
 * GParted_Core class.
 * This class provides support for motherboard based RAID devices, also know
 * as Fake RAID.
 * Static elements are used in order to reduce the disk accesses required to
 * load the data structures upon each initialization of the class.
 */

#ifndef DMRAID_H_
#define DMRAID_H_

#include "../include/Utils.h"
#include "../include/Partition.h"
#include "../include/OperationDetail.h"

#include <vector>

//Declare some constants
const Glib::ustring DEV_MAP_PATH = "/dev/mapper/" ;

namespace GParted
{


class DMRaid
{
public:
	DMRaid() ;
	DMRaid( const bool & do_refresh ) ;
	~DMRaid() ;
	bool is_dmraid_supported() ;
	bool is_dmraid_device( const Glib::ustring & dev_path ) ;
	int execute_command( const Glib::ustring & command, OperationDetail & operationdetail ) ;
	void get_devices( std::vector<Glib::ustring> & dmraid_devices ) ;
	Glib::ustring get_dmraid_name( const Glib::ustring & dev_path ) ;
	Glib::ustring get_dmraid_prefix( const Glib::ustring & dev_path ) ;
	int get_partition_number( const Glib::ustring & partition_name ) ;
	bool create_dev_map_entries( const Partition & partition, OperationDetail & operationdetail ) ;
	bool create_dev_map_entries( const Glib::ustring & dev_path ) ;
	bool delete_affected_dev_map_entries( const Partition & partition, OperationDetail & operationdetail ) ;
	bool delete_dev_map_entry( const Partition & partition, OperationDetail & operationdetail ) ;
	bool partition_is_mounted_by_path( const Glib::ustring & partition_path
	                                 , const std::vector<Glib::ustring> & mount_info ) ;
	bool purge_dev_map_entries( const Glib::ustring & dev_path ) ;
	bool update_dev_map_entry( const Partition & partition, OperationDetail & operationdetail ) ;
private:
	void load_dmraid_cache() ;
	void set_commands_found() ;
	void get_dmraid_dir_entries( const Glib::ustring & dev_path, std::vector<Glib::ustring> & dir_list ) ;
	void get_affected_dev_map_entries( const Partition & partition, std::vector<Glib::ustring> & affected_entries ) ;
	void get_partition_dev_map_entries( const Partition & partition, std::vector<Glib::ustring> & partition_entries ) ;
	static bool dmraid_cache_initialized ;
	static bool dmraid_found ;
	static bool dmsetup_found ;
	static bool kpartx_found ;
	static std::vector<Glib::ustring> dmraid_devices ;
};

}//GParted

#endif /* DMRAID_H_ */