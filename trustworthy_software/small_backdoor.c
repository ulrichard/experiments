{
    Channel *c;
-   if (id < 0 || id > channels_alloc)
+   if (id < 0 || id >= channels_alloc)
    {
        log("channel_lookup: %d: bad id", id);
        return NULL;
    }
}
