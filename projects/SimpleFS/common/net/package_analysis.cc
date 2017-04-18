namespace net {

	PackageAnalysis::PackageAnalysis() : receive_packages_(std::unordered_map<sint32_t, NetReceiveData_t>()) {};

	PackageAnalysis::~PackageAnalysis() {}

	void PackageAnalysis::Register(int32_t id)
	{
		receive_package_.insert(id, NetReceiveData_t());
	}	 


	bool PackageAnalysis::TcpDataSplitt(int32_t id, const char* recv_data, size_t recv_size)
	{
		NetReceiveData_t& receive_data = receive_package_[id];
		if(receive_data.bFirst)
		{
			memset(receive_data.szLastSaveData, 0, sizeof(receive_data.szLastSaveData));
			receive_data.bFirst = false;
		}

		memcpy(static_cast<char*>(receive_data.szLastSaveData + receive_data.nRemainSize), recv_data, recv_size);
		receive_data.nRemainSize += recv_size;
		NetDataHeader_t* data_head = reinterpret_cast<NetDataHeader_t*>(receive_data.szLastSaveData);
		while(receive_data.nRemainSize >= sizeof(NetDataHeader_t) + data_header.nDataSize)
		{
			HandleNetPack(data_header);
			int recv_object_size = sizeof(NetDataHeader_t) + data_header.nDataSize;
			receive_data.nRemainSize -= recv_object_size;
			data_head = reinterpret_cast<NetDataHeader_t>(static_cast<char*>(data_head + recv_object_size));
		}
		if(receive_data.szLastSaveData != static_cast<char*>(data_head))
		{
			memmove(receive_data.szLastSaveData, static_cast<char*>(data_head), receive_data.nRemainSize);
			memset(static_cast<char*>(receive_data.szLastSaveData), 0,
					 sizeof(receive_data.szLastSaveData) - receive_data.nRemainSize);
			
		}
		return true;
	}

}
