#include <network/packet/ChunkDataPacket.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <network/PacketIds.h>
#include <network/NetEventCallback.hpp>
ChunkDataPacket::ChunkDataPacket() {
}
ChunkDataPacket::ChunkDataPacket(int32_t x, int32_t z, LevelChunk* chunk) {
	this->xPos = x;
	this->zPos = z;
	this->chunk = chunk;
}
ChunkDataPacket::~ChunkDataPacket() {
}
void ChunkDataPacket::write(RakNet::BitStream* stream) {
	stream->Write<uint8_t>(PID_CHUNK_DATA_PACKET);
	stream->Write<int32_t>(this->xPos);
	stream->Write<int32_t>(this->zPos);
	this->stream.Reset();
	for(int32_t v4 = 0; v4 != 256; ++v4) {
		uint8_t um = this->chunk->updateMap[v4];
		this->stream.Write<uint8_t>(um);
		if(um) {
			for(int32_t i = 0; i != 8; ++i) {
				if((((int32_t)um >> i) & 1) != 0) {
					int32_t index = (((v4 & 0xF) << 11) | (v4 >> 4 << 7)) + 16 * i;
					this->stream.Write((char*)&this->chunk->tiles[index], 0x10u);
					this->stream.Write((char*)&this->chunk->tileMeta.data[index >> 1], 0x8u);
				}
			}
		}
	}
}
void ChunkDataPacket::read(RakNet::BitStream* stream) {
	stream->Read<int32_t>(this->xPos);
	stream->Read<int32_t>(this->zPos);
	stream->Read(this->stream);
}
void ChunkDataPacket::handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
	a3->handle(a2, this);
}
