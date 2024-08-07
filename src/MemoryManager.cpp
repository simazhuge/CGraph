#include "MemoryManager.h"

CGraph::MemoryManager::MemoryManager() {}

void CGraph::MemoryManager::deletePipeline(GPipeline *line)
{
    auto it = m_insCecheMap.find(line);
    if (it != m_insCecheMap.end()) {
        it->second->deallocate(line);
        it->second->destroy(line);
        m_insCecheMap.erase(it); // 删除找到的元素
    } else {
        assert("some memory error");
    }
}

CGraph::GPipeline *CGraph::MemoryManager::createPipeine()
{
    //TODO 优化
    CGraph::GPipeline * ret{nullptr};
    for(auto iter = m_listCache.begin(); iter != m_listCache.end(); ++iter)
    {
        if(iter->size < PIPLELINE_CACHE_SIZE)
        {
            ret = iter->cache->allocate(1);
            iter->cache->construct(ret);
            iter->size++;
            m_insCecheMap.insert(std::make_pair(ret, iter->cache));
            break;
        }
    }
    if(ret == nullptr)
    {
        auto tmp = new PipeLineCache;
        ret = tmp->allocate(1);
        tmp->construct(ret);
        m_insCecheMap.insert(std::make_pair(ret, tmp));
        PipelineSizePair pair;
        pair.cache = tmp;
        m_listCache.push_back(pair);
    }

    return ret;
}
