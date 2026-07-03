---

## 📋 Problem Catalog (P01 - P50)

### P01 - Kernel-style ring buffer (kfifo-like) `[DS]`
* **Description:** Used by: kernel log, serial drivers, DMA descriptors. Constraint: capacity must be a power of two (allows mask instead of modulo). full when `(head - tail) == cap`, empty when `head == tail`.
* **Hint:** 💡 `head` & `tail` are ever-increasing; `index = val & (cap-1)`
* **Function Signatures:**
```c
int      rb_init(RingBuffer *rb, uint32_t cap);
void     rb_destroy(RingBuffer *rb);
int      rb_push(RingBuffer *rb, uint8_t byte);
int      rb_pop(RingBuffer *rb, uint8_t *out);

```

### P02 - Simple inode cache (hash table + LRU eviction) `[DS]`

* **Description:** Mimics Linux dcache/icache behaviour. Fixed capacity `INODE_CACHE_SIZE=64` slots. On lookup miss + cache full: evict the least recently used entry.
* **Function Signatures:**

```c
void         ic_init(InodeCache *c);
void         ic_insert(InodeCache *c, uint64_t ino, uint32_t mode, uint64_t size);
void         ic_evict(InodeCache *c, uint64_t ino);
int          ic_count(const InodeCache *c);

```

### P03 - Fixed-size slab allocator (kernel kmem_cache style) `[DS]`

* **Description:** Pre-allocates a slab of N objects of fixed `obj_size`. `alloc()` returns a free slot in O(1); `free()` returns it. Use a free-list of indices stored inside free slots (intrusive).
* **Function Signatures:**

```c
SlabCache *slab_create(size_t obj_size, size_t capacity);
void       slab_destroy(SlabCache *sc);
void      *slab_alloc(SlabCache *sc);
void       slab_free(SlabCache *sc, void *ptr);

```

### P04 - Wait-queue (simulated, no real threads) `[DS]`

* **Description:** Models Linux `wait_queue_head_t`: tasks block until a condition is met. Simplified: tasks are represented by integer IDs. `wake_one()` removes and returns the head task; `wake_all()` drains the queue.
* **Function Signatures:**

```c
void wq_init(WaitQueue *wq);
int  wq_add(WaitQueue *wq, int task_id);
int  wq_wake_one(WaitQueue *wq);
int  wq_wake_all(WaitQueue *wq, int *out, int out_sz);

```

### P05 - kfifo bulk read/write (byte stream, not single byte) `[DS]`

* **Description:** Extend P01: push/pop N bytes at once (like serial driver DMA burst). Returns bytes actually written/read (may be less than requested if near full/empty).
* **Function Signatures:**

```c
int    kf_init(KFifo *kf, uint32_t cap);
void   kf_destroy(KFifo *kf);
size_t kf_write(KFifo *kf, const uint8_t *data, size_t len);
size_t kf_read(KFifo *kf, uint8_t *out, size_t len);

```

### P06 - Device registry (udev-style) `[Driver]`

* **Description:** Register devices by `(bus, devnum)`. Lookup by either. Supports probe/remove lifecycle callbacks (function pointers). Max 32 devices.
* **Function Signatures:**

```c
void         dr_init(DeviceRegistry *r);
int          dr_register(DeviceRegistry *r, uint8_t bus, uint32_t devnum, const char *name, probe_fn p, remove_fn rm);
DeviceEntry *dr_lookup(DeviceRegistry *r, uint8_t bus, uint32_t devnum);
int          dr_remove(DeviceRegistry *r, uint8_t bus, uint32_t devnum);

```

### P07 - GPIO interrupt mask register operations `[Driver]`

* **Description:** Simulates a 32-bit MMIO interrupt mask register (each bit = one GPIO line). Common in Linux gpio/irqchip drivers.
* **Function Signatures:**

```c
void     gpio_irq_init(GpioIrqCtrl *g);
void     gpio_irq_enable(GpioIrqCtrl *g, int pin);
void     gpio_irq_disable(GpioIrqCtrl *g, int pin);
bool     gpio_irq_is_enabled(const GpioIrqCtrl *g, int pin);

```

### P08 - MMIO register read/write helpers `[Driver]`

* **Description:** Simulates `readl`/`writel`/`readw`/`writeb` used in Linux device drivers. Uses a byte array as the "device MMIO window". All accesses must be volatile and respect alignment.
* **Function Signatures:**

```c
void     mmio_init(MmioRegion *r);
void     mmio_write32(MmioRegion *r, uint32_t offset, uint32_t val);
uint32_t mmio_read32(const MmioRegion *r, uint32_t offset);
void     mmio_write8(MmioRegion *r, uint32_t offset, uint8_t val);

```

### P09 - sysfs attribute parser `[Driver]`

* **Description:** Parse `key=value` pairs as written to a sysfs node. Format: `"key=value\n"` or `"key=value"` (newline optional). Supports int, bool (`0`/`1`/`true`/`false`/`on`/`off`), and string values.
* **Function Signatures:**

```c
int sysfs_parse(const char *buf, SysfsAttr *out);
int sysfs_parse_int(const char *buf, long *out);
int sysfs_parse_bool(const char *buf, bool *out);

```

### P10 - /proc/meminfo style parser `[Driver]`

* **Description:** Parse lines of the form `"FieldName: <value> kB"` from a buffer (not from the actual filesystem — buffer passed in). Return the value for a given key, or -1 if not found.
* **Function Signatures:**

```c
long proc_get_field_kb(const char *buf, const char *key);
long proc_get_field_bytes(const char *buf, const char *key);
int  proc_count_fields(const char *buf);

```

### P11 - Software timer wheel (simplified Linux hrtimer/timer_list) `[DS]`

* **Description:** Fixed 256-slot wheel, 1 tick = 1ms. Timers fire when the wheel hand reaches their slot. Supports single-shot and periodic timers.
* **Function Signatures:**

```c
void tw_init(TimerWheel *tw);
int  tw_add(TimerWheel *tw, TimerNode *t, uint32_t delay_ticks, uint32_t period);
void tw_tick(TimerWheel *tw);
int  tw_cancel(TimerWheel *tw, TimerNode *t);

```

### P12 - Snap version string comparison `[snapd]`

* **Description:** Snap uses `epoch:upstream~debian` style versioning (subset of deb). Implement comparison returning `<0`, `0`, `>0` (like `strcmp`). Rules: compare epoch first (int), then upstream char-by-char digits compared numerically, non-digits compared by ASCII.
* **Function Signatures:**

```c
int  snap_version_cmp(const char *a, const char *b);
bool snap_version_satisfies(const char *ver, const char *constraint);

```

### P13 - Debian control file parser (subset) `[snapd]`

* **Description:** Parse `"Field: value\n"` multi-line format as found in `/var/lib/dpkg/status`. Support multi-line values (continuation lines start with a space).
* **Function Signatures:**

```c
int         deb_parse(const char *buf, DebControl *out);
const char *deb_get(const DebControl *c, const char *key);

```

### P14 - udev uevent filter `[snapd]`

* **Description:** uevents arrive as `"KEY=VALUE\0KEY=VALUE\0..."` null-separated strings. Implement a simple rule matcher: match if ALL specified `key=value` pairs match. Used in udev rules and snapd device assignment.
* **Function Signatures:**

```c
void uf_init(UeventFilter *f);
int  uf_add_rule(UeventFilter *f, const char *key, const char *val);
bool uf_matches(const UeventFilter *f, const char *uevent_buf, size_t len);
const char *uf_get_value(const char *uevent_buf, size_t len, const char *key);

```

### P15 - cgroup resource counter (memory.usage_in_bytes style) `[snapd]`

* **Description:** Hierarchical counter: child charges propagate up to parent. Supports limit enforcement and overflow detection.
* **Function Signatures:**

```c
void     cgt_init(CGroupTree *t);
int      cgt_add(CGroupTree *t, const char *name, uint64_t limit, int parent_idx);
int      cgt_charge(CGroupTree *t, int idx, uint64_t bytes);
void     cgt_uncharge(CGroupTree *t, int idx, uint64_t bytes);

```

### P16 - Netlink message ring (variable-length messages) `[FSM]`

* **Description:** Store variable-length netlink-style messages in a contiguous ring buffer. Each message is prefixed with a 4-byte length header. If a message does not fit, drop it and increment `drop_count`.
* **Function Signatures:**

```c
int    nlr_init(NlRing *r, uint32_t cap);
void   nlr_destroy(NlRing *r);
int    nlr_push(NlRing *r, const void *msg, uint32_t len);
int    nlr_pop(NlRing *r, void *out, uint32_t *len);

```

### P17 - ioctl command dispatch table `[Driver]`

* **Description:** Map ioctl command numbers to handler functions (like a driver's `unlocked_ioctl`). Supports up to 32 registered commands. Unknown cmd returns `-ENOTTY` (-25).
* **Function Signatures:**

```c
void ioctl_table_init(IoctlTable *t);
int  ioctl_register(IoctlTable *t, uint32_t cmd, ioctl_fn fn);
long ioctl_dispatch(const IoctlTable *t, uint32_t cmd, unsigned long arg);
int  ioctl_unregister(IoctlTable *t, uint32_t cmd);

```

### P18 - DMA scatter-gather list builder `[Driver]`

* **Description:** DMA transfers use scatter-gather lists: arrays of `(phys_addr, length)` pairs. Build an sg list from a virtual buffer, respecting a `max_seg_size` constraint. (Simulated: `phys_addr = (uintptr_t)virt_addr` for testing.)
* **Function Signatures:**

```c
int sg_build(SgList *sg, const void *buf, size_t total_len, size_t max_seg);
size_t sg_total_len(const SgList *sg);
int    sg_nents(const SgList *sg);

```

### P19 - Device power state machine (Linux PM: D0/D1/D2/D3) `[Driver]`

* **Description:** Implement transitions and transition validation. Invalid transitions must be rejected. Track transition count and time-in-state (simulated tick counter).
* **Function Signatures:**

```c
void   pwr_init(PowerDev *d);
int    pwr_transition(PowerDev *d, DState target);
void   pwr_tick(PowerDev *d);
bool   pwr_is_active(const PowerDev *d);

```

### P20 - Software watchdog timer `[Driver]`

* **Description:** A watchdog must be "kicked" (reset) before its timeout expires. If not kicked in time, it fires a callback (simulating a system reset). Supports enable/disable and timeout reconfiguration.
* **Function Signatures:**

```c
void wdt_init(Watchdog *w, uint32_t timeout, wdt_expire_fn fn, void *arg);
void wdt_enable(Watchdog *w);
void wdt_disable(Watchdog *w);
void wdt_kick(Watchdog *w);

```

### P21 - mmap region tracker `[Driver]`

* **Description:** Track mapped memory regions `[start, start+len)`. Support overlap detection, merge of adjacent regions, and unmapping. Max 32 regions.
* **Function Signatures:**

```c
void  mm_init(MmapTracker *t);
int   mm_map(MmapTracker *t, uintptr_t start, size_t len, int prot);
int   mm_unmap(MmapTracker *t, uintptr_t start, size_t len);
bool  mm_is_mapped(const MmapTracker *t, uintptr_t addr);

```

### P22 - Device tree property parser `[Driver]`

* **Description:** Device tree properties are byte blobs. Common types: u32 cell list, string list, reg (addr+size pairs). Parse a property blob into typed values.
* **Function Signatures:**

```c
int  dt_read_u32(const uint8_t *prop, size_t len, int idx, uint32_t *out);
int  dt_read_u64(const uint8_t *prop, size_t len, int idx, uint64_t *out);
int  dt_read_string(const uint8_t *prop, size_t len, int idx, char *out, size_t out_sz);
int  dt_read_reg(const uint8_t *prop, size_t len, int idx, uint32_t *addr, uint32_t *size);

```

### P23 - Firmware image CRC32 verifier `[Driver]`

* **Description:** Firmware images end with a 4-byte CRC32 (little-endian). Verify integrity and compute CRC for new images. Use CRC32 polynomial `0xEDB88320` (IEEE 802.3, same as Linux kernel).
* **Function Signatures:**

```c
uint32_t fw_crc32(const uint8_t *data, size_t len);
bool     fw_verify(const uint8_t *image, size_t image_len);
void     fw_append_crc(uint8_t *image, size_t data_len);

```

### P24 - Linux kernel boot argument parser `[snapd]`

* **Description:** Parse cmdline strings like `"console=ttyS0,115200 root=/dev/sda1 ro quiet"` Extract: presence of flags, values of `key=value` params.
* **Function Signatures:**

```c
bool        bootarg_has_flag(const char *cmdline, const char *flag);
const char *bootarg_get_value(const char *cmdline, const char *key, char *out, int out_sz);
int         bootarg_count(const char *cmdline);
int         bootarg_parse_console(const char *cmdline, char *dev, int dev_sz, int *baud);

```

### P25 - Kernel circular log buffer (dmesg-style) `[snapd]`

* **Description:** Variable-length text messages stored in a ring. Each record: `[uint16_t len][uint8_t level][char text[len]]`. Oldest records are overwritten when buffer is full.
* **Function Signatures:**

```c
void log_init(LogBuf *lb);
int  log_write(LogBuf *lb, uint8_t level, const char *msg);
int  log_read_next(LogBuf *lb, uint8_t *level, char *out, size_t out_sz);
int  log_count(const LogBuf *lb);

```

### P26 - PID table (kernel pidmap-lite) `[snapd]`

* **Description:** Allocate and free PIDs from a bitmap. Max 1024 PIDs. PID 0 and 1 are always reserved. `alloc_pid()` returns the lowest available PID.
* **Function Signatures:**

```c
void pid_map_init(PidMap *pm);
int  pid_alloc(PidMap *pm);
void pid_free(PidMap *pm, int pid);
int  pid_in_use(const PidMap *pm, int pid);

```

### P27 - /proc/mounts parser `[snapd]`

* **Description:** Format: `"device mountpoint fstype options dump pass\n"`. Build a searchable table of mount entries.
* **Function Signatures:**

```c
int          mt_parse(const char *buf, MountTable *out);
int          mt_count_fstype(const MountTable *t, const char *fstype);

```

### P28 - Signal set / bitmask (sigset_t-lite) `[snapd]`

* **Description:** Linux signals 1..64 stored in a two-word bitmask. Implement the full `sigset_t` API subset.
* **Function Signatures:**

```c
void sigset_empty(SigSet *s);
void sigset_fill(SigSet *s);
void sigset_add(SigSet *s, int signo);
void sigset_del(SigSet *s, int signo);

```

### P29 - sysctl node table (proc_dointvec style) `[snapd]`

* **Description:** Register integer sysctl variables with min/max validation. Read/write via path strings like `"kernel/pid_max"`.
* **Function Signatures:**

```c
void sysctl_init(SysctlTable *t);
int  sysctl_register(SysctlTable *t, const char *path, int *var, int min, int max);
int  sysctl_read(const SysctlTable *t, const char *path, int *out);
int  sysctl_write(SysctlTable *t, const char *path, int val);

```

### P30 - OOM killer score calculator `[snapd]`

* **Description:** Linux OOM killer selects the process with the highest `oom_score`. `score = (rss_pages * 1000 / total_pages) + oom_score_adj`. `oom_score_adj` range: -1000..1000. Select the victim from a table of processes.
* **Function Signatures:**

```c
void oom_init(OomTable *t, uint64_t total_pages);
int  oom_add_proc(OomTable *t, int pid, uint64_t rss, int adj, const char *name);
int  oom_score(const OomTable *t, int idx);
int  oom_select_victim(const OomTable *t);

```

### P31 - Packed sensor data frame (IoT protocol encoding) `[Bits]`

* **Description:** Sensor transmits 4-byte frames: `[temp:12bit][humidity:10bit][status:4bit][alert:6bit]`. All big-endian bit-packed from MSB. Implement encode/decode without structs (raw `uint32_t`).
* **Function Signatures:**

```c
uint32_t sensor_encode(uint16_t temp_raw, uint16_t humid_raw, uint8_t status, uint8_t alert);
void     sensor_decode(uint32_t frame, uint16_t *temp, uint16_t *humid, uint8_t *status, uint8_t *alert);
bool     sensor_frame_valid(uint32_t frame);

```

### P32 - Endianness conversion (like Linux cpu_to_be32 / le32_to_cpu) `[Bits]`

* **Description:** Implement without relying on compiler builtins (for portability). Also implement network byte-order helpers (`htons`/`htonl` equivalent).
* **Function Signatures:**

```c
uint16_t bswap16(uint16_t x);
uint32_t bswap32(uint32_t x);
uint64_t bswap64(uint64_t x);
uint32_t cpu_to_be32(uint32_t x);

```

### P33 - CRC32 with incremental update (like Linux lib/crc32.c) `[Bits]`

* **Description:** Used for: block device checksums, firmware integrity, snap assertions. Support incremental computation across multiple buffers.
* **Function Signatures:**

```c
uint32_t crc32_init(void);
uint32_t crc32_update(uint32_t crc, const uint8_t *buf, size_t len);
uint32_t crc32_final(uint32_t crc);
uint32_t crc32_buf(const uint8_t *buf, size_t len);

```

### P34 - Hardware register bitfield accessor (FIELD_GET/FIELD_PREP style) `[Bits]`

* **Description:** Linux kernel uses `FIELD_GET(mask, val)` and `FIELD_PREP(mask, val)`. Implement a portable version without `typeof`/`__builtin_ctzl`. mask encodes both position and width: e.g. `0x00FF0000` = bits 16..23.
* **Function Signatures:**

```c
uint32_t reg_field_get(uint32_t reg, uint32_t mask);
uint32_t reg_field_prep(uint32_t val, uint32_t mask);
uint32_t reg_field_set(uint32_t reg, uint32_t mask, uint32_t val);
uint32_t reg_field_clear(uint32_t reg, uint32_t mask);

```

### P35 - Run-length encoding for binary firmware patches `[Bits]`

* **Description:** Format: `[count:u8][byte:u8]` pairs. `count=0` is invalid (skip). Used in delta firmware update compression.
* **Function Signatures:**

```c
int rle_encode(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);
int rle_decode(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);

```

### P36 - Hex dump formatter (like kernel print_hex_dump) `[Bits]`

* **Description:** Output: `"0000: 01 02 03 04  05 06 07 08  |........|\n"` 16 bytes per line, offset prefix, ASCII column. Used for debugging memory, registers, and network packets.
* **Function Signatures:**

```c
int  hex_dump(const uint8_t *buf, size_t len, char *out, size_t out_cap);
int  hex_parse(const char *hexstr, uint8_t *out, size_t out_cap);
void byte_to_hex(uint8_t b, char *hi, char *lo);

```

### P37 - argv/getopt-style argument parser `[Bits]`

* **Description:** Parse a command-line string into `argc`/`argv` (like `wordexp` without shell). Support quoted strings and escaped spaces. Also implement a simple flag parser: `-f`, `--flag`, `--key=value`.
* **Function Signatures:**

```c
int  argv_parse(const char *cmdline, ArgList *out);
bool argv_has_flag(const ArgList *al, const char *flag);
const char *argv_get_value(const ArgList *al, const char *key);

```

### P38 - Environment variable store (snapd/systemd unit env parsing) `[Bits]`

* **Description:** Parse `"KEY=VALUE\n"` format environment files. Support variable expansion: `VALUE` can reference `$OTHER_KEY`. Max depth 4 expansion.
* **Function Signatures:**

```c
void        env_init(EnvStore *e);
int         env_set(EnvStore *e, const char *key, const char *val);
const char *env_get(const EnvStore *e, const char *key);
int         env_parse_file(const char *buf, EnvStore *e);

```

### P39 - Lock-free stack using GCC atomics (used in kernel-bypass paths) `[DS]`

* **Description:** Implement using `__atomic_compare_exchange_n`. Nodes are caller-allocated (intrusive). Max 64 nodes.
* **Function Signatures:**

```c
void  lfs_init(LFStack *s);
void  lfs_push(LFStack *s, LFNode *node);
LFNode *lfs_pop(LFStack *s);
bool  lfs_empty(const LFStack *s);

```

### P40 - Spinlock and ticket lock simulation `[DS]`

* **Description:** Implement a test-and-set spinlock and a ticket lock using GCC `__atomic`. Track contention statistics (times spun, total acquires).
* **Function Signatures:**

```c
void spin_init(SpinLock *l);
void spin_lock(SpinLock *l);
bool spin_trylock(SpinLock *l);
void spin_unlock(SpinLock *l);

```

### P41 - Work queue (kernel workqueue-lite) `[DS]`

* **Description:** Deferred work items executed in submission order. Supports delayed items (run after N ticks) and cancellation.
* **Function Signatures:**

```c
void wq_init(WorkQueue *wq);
int  wq_submit(WorkQueue *wq, work_fn fn, void *arg, uint32_t delay_ticks);
int  wq_cancel(WorkQueue *wq, int id);
int  wq_run_pending(WorkQueue *wq);

```

### P42 - Reference counting with saturation (like Linux kref / refcount_t) `[DS]`

* **Description:** Saturates at `UINT32_MAX` (never wraps). Decrement to 0 calls release cb. Protect against use-after-free by detecting `get()` on a zero refcount.
* **Function Signatures:**

```c
void rc_init(RefCount *rc, void *obj, release_fn fn);
bool rc_get(RefCount *rc);
bool rc_put(RefCount *rc);
uint32_t rc_read(const RefCount *rc);

```

### P43 - UART framing FSM `[DS]`

* **Description:** Protocol: `[START:0xAA][LEN:u8][PAYLOAD:LEN bytes][CRC8:u8]` FSM processes one byte at a time (interrupt-driven style). States: IDLE -> SYNC -> LENGTH -> PAYLOAD -> CHECKSUM -> DONE/ERROR
* **Function Signatures:**

```c
void uart_fsm_init(UartFsm *f);
int  uart_fsm_feed(UartFsm *f, uint8_t byte);
void uart_fsm_reset(UartFsm *f);
uint8_t uart_crc8(const uint8_t *data, uint8_t len);

```

### P44 - USB device enumeration state machine `[DS]`

* **Description:** Models the USB device state machine from USB 2.0 spec: Attached -> Powered -> Default -> Address -> Configured -> Suspended. Implement legal transitions and violation detection.
* **Function Signatures:**

```c
void usb_dev_init(UsbDev *d);
int  usb_dev_event(UsbDev *d, UsbEvent ev);
bool usb_dev_is_ready(const UsbDev *d);
const char *usb_state_name(UsbState s);

```

### P45 - Memory pool with alignment support `[DS]`

* **Description:** Arena allocator: bump pointer inside a fixed buffer. Supports alignment requirements (4, 8, 16, 64 byte). `reset()` frees entire pool at once (no per-object free).
* **Function Signatures:**

```c
int   mp_init(MemPool *mp, size_t cap);
void  mp_destroy(MemPool *mp);
void *mp_alloc(MemPool *mp, size_t size, size_t align);
void  mp_reset(MemPool *mp);

```

### P46 - Buddy allocator (simplified Linux page allocator) `[DS]`

* **Description:** Manages 64 pages of size `PAGE_SIZE=4096`. Allocate in power-of-two page counts only. On free, merge with buddy if both are free.
* **Function Signatures:**

```c
void  buddy_init(BuddyAlloc *b);
int   buddy_alloc(BuddyAlloc *b, int npages);
void  buddy_free(BuddyAlloc *b, int page_idx, int npages);
bool  buddy_page_free(const BuddyAlloc *b, int page_idx);

```

### P47 - Lightweight red-black tree (subset) `[DS]`

* **Description:** Kernel uses rbtree for process scheduling (CFS), mm, timers. Implement: insert, lookup, in-order traversal only. Color balancing required for insert (left-rotate, right-rotate, recolor).
* **Function Signatures:**

```c
void     rbt_init(RbTree *t);
int      rbt_insert(RbTree *t, RbNode *node, uint64_t key, void *val);
void     rbt_inorder(const RbTree *t, void (*visit)(RbNode *));
int      rbt_count(const RbTree *t);

```

### P48 - LRU cache with hash map (like Linux page cache / dcache) `[DS]`

* **Description:** Combine a hash table for O(1) lookup with a doubly-linked LRU list. On capacity: evict LRU entry before inserting new one. Capacity: 32 entries, key: uint64_t, value: uint64_t.
* **Function Signatures:**

```c
void     lru_init(LruCache *c);
void     lru_put(LruCache *c, uint64_t key, uint64_t val);
bool     lru_get(LruCache *c, uint64_t key, uint64_t *val);
void     lru_evict_lru(LruCache *c);

```

### P49 - CPU affinity map (cpumask_t-lite) `[snapd]`

* **Description:** Track which CPUs are allowed for a task (like taskset / `sched_setaffinity`). Operations on bitmasks up to 64 CPUs.
* **Function Signatures:**

```c
void     cm_zero(CpuMask *m);
void     cm_fill(CpuMask *m, int ncpus);
void     cm_set(CpuMask *m, int cpu);
void     cm_clear(CpuMask *m, int cpu);

```

### P50 - Snap health check state tracker (snapd snap.health API) `[snapd]`

* **Description:** Snaps report health: ok/waiting/blocked/error with optional message. Track history (last 8 states), detect repeated errors, emit alerts.
* **Function Signatures:**

```c
void   sh_init(SnapHealth *h);
void   sh_report(SnapHealth *h, HealthStatus s, const char *msg);
void   sh_tick(SnapHealth *h);
bool   sh_is_critical(const SnapHealth *h);

```
