#include "BookOrbitSyncBackdrop.h"

#include <GfxRenderer.h>
#include <HalStorage.h>
#include <Logging.h>

namespace BookOrbitSyncBackdrop {
namespace {
constexpr char FILE_PATH[] = "/.crosspoint/bookorbit_sync_backdrop.bin";
}

bool save(GfxRenderer& renderer) {
  discard();
  const uint8_t* frame = renderer.getFrameBuffer();
  const size_t size = renderer.getBufferSize();
  if (frame == nullptr || size == 0) return false;
  FsFile file;
  if (!Storage.openFileForWrite("BOSB", FILE_PATH, file)) return false;
  const size_t written = file.write(frame, size);
  file.close();
  if (written != size) {
    LOG_ERR("BOSB", "Short write of the sync backdrop (%u of %u)", static_cast<unsigned>(written),
            static_cast<unsigned>(size));
    discard();
    return false;
  }
  return true;
}

bool exists() { return Storage.exists(FILE_PATH); }

bool load(GfxRenderer& renderer) {
  uint8_t* frame = renderer.getFrameBuffer();
  const size_t size = renderer.getBufferSize();
  if (frame == nullptr || size == 0) return false;
  FsFile file;
  if (!Storage.openFileForRead("BOSB", FILE_PATH, file)) return false;
  bool ok = file.fileSize() == size && file.read(frame, size) == static_cast<int>(size);
  file.close();
  if (!ok) LOG_ERR("BOSB", "Sync backdrop unreadable or for another panel size");
  return ok;
}

void discard() {
  if (Storage.exists(FILE_PATH)) Storage.remove(FILE_PATH);
}

}  // namespace BookOrbitSyncBackdrop
