async function configure_WebGPU() {
    if (navigator.gpu !== undefined && navigator.gpu !== null)
    {
        const adapter = await navigator.gpu.requestAdapter();
        if (adapter !== undefined && adapter !== null)
        {
            const device = await adapter.requestDevice();
            if (device !== undefined && device !== null)
            {
                window.bWebGPUEnabled = true;
                Module.preinitializedWebGPUDevice = device;
                return;
            }
        }
        window.bWebGPUEnabled = false;
    }
}
configure_WebGPU();