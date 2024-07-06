async function configure_WebGPU() {
    if (navigator.gpu !== undefined && navigator.gpu !== null)
    {
        const adapter = await navigator.gpu.requestAdapter();
        const device = await adapter.requestDevice();
        Module.preinitializedWebGPUDevice = device;
    }
}
configure_WebGPU();