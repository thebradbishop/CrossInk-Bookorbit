#pragma once

class GfxRenderer;

/**
 * The screen a BookOrbit sync was started over, kept on the SD card across the network
 * restart so the sync can show its status as a banner over it instead of a screen of its
 * own. The restart empties the frame buffer while the panel still shows that screen, and
 * not every panel can refresh a window, so the whole frame is put back before each banner.
 *
 * Saved by a sync started from a screen (silentRestartToNetwork), and by the sleep screen
 * when Sync on Wake is on: a wake has nothing in the frame buffer, but the panel shows the
 * sleep screen. One frame (about 50 KB), removed when the sync ends.
 */
namespace BookOrbitSyncBackdrop {

bool save(GfxRenderer& renderer);
bool exists();
// Copies the saved frame into the frame buffer; false (buffer untouched) when there is
// none or it does not match this panel's frame size.
bool load(GfxRenderer& renderer);
void discard();

}  // namespace BookOrbitSyncBackdrop
