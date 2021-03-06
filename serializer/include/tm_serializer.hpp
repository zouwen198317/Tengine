/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2018, Open AI Lab
 * Author: jingyou@openailab.com
 */
#ifndef __TM_SERIALIZER_HPP__
#define __TM_SERIALIZER_HPP__

#include "serializer.hpp"
#include "static_graph_interface.hpp"
#include "logger.hpp"
#include "tm_generate.h"

namespace TEngine {

class TmSerializer : public Serializer {

public:
    TmSerializer() { 
        name_="tm_loader";
        version_="0.1";
        format_name_="tengine";
    }

    virtual ~TmSerializer() {};

    unsigned int GetFileNum(void) override { return 1; }

    bool LoadModel(const std::vector<std::string>& file_list, StaticGraph *graph) override;
    bool SaveModel(const std::vector<std::string>& file_list, Graph *graph) override;

    bool LoadConstTensor(const std::string& fname, StaticTensor * const_tensor) override {return false; }
    bool LoadConstTensor(int fd, StaticTensor * const_tensor) override { return false; }

protected:
    bool LoadBinaryFile(const char * tm_fname);
    bool LoadNode(StaticGraph *graph, StaticNode *node, const TM_Node *tm_node);
    bool LoadTensor(StaticGraph *graph, const TM_Tensor *tm_tensor, const TM_Buffer *tm_buf);
    bool LoadGraph(StaticGraph *graph, const TM_Model *tm_model);

private:
    int mmap_fd_;
    void *mmap_buf_;
    size_t mmap_buf_size_;

};

} //namespace TEngine

#endif
