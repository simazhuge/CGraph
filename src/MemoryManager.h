#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "CBasic/CBasicDefine.h"
#include "GraphCtrl/GraphPipeline/GPipeline.h"
#include "MemoryPool.h"
#include "singleton.h"
#define PIPLELINE_CACHE_SIZE 100
CGRAPH_NAMESPACE_BEGIN
class MemoryManager : public singleton<MemoryManager>
{
public:
    typedef MemoryPool<GPipeline, PIPLELINE_CACHE_SIZE * sizeof(GPipeline)>  PipeLineCache;
    struct PipelineSizePair{
        PipeLineCache *cache{nullptr};
        int size{0};
    };
    MemoryManager();
    GPipeline *createPipeine();
    void deletePipeline(GPipeline *);
    //TODO 释放资源
private:
    std::unordered_map<GPipeline *, PipeLineCache *> m_insCecheMap;
    std::list<PipelineSizePair > m_listCache;
};
CGRAPH_NAMESPACE_END
#endif // MEMORYMANAGER_H
